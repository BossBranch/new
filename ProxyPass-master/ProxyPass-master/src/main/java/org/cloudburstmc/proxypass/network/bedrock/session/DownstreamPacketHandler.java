package org.cloudburstmc.proxypass.network.bedrock.session;

import com.fasterxml.jackson.annotation.JsonInclude;
import com.fasterxml.jackson.annotation.JsonProperty;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.RequiredArgsConstructor;
import lombok.Value;
import lombok.extern.log4j.Log4j2;
import org.cloudburstmc.nbt.*;
import org.cloudburstmc.nbt.util.stream.LittleEndianDataOutputStream;
import org.cloudburstmc.protocol.bedrock.BedrockSession;
import org.cloudburstmc.protocol.bedrock.data.biome.BiomeDefinitionData;
import org.cloudburstmc.protocol.bedrock.data.definitions.BlockDefinition;
import org.cloudburstmc.protocol.bedrock.data.definitions.ItemDefinition;
import org.cloudburstmc.protocol.bedrock.data.definitions.SimpleItemDefinition;
import org.cloudburstmc.protocol.bedrock.data.inventory.CreativeItemData;
import org.cloudburstmc.protocol.bedrock.data.inventory.CreativeItemGroup;
import org.cloudburstmc.protocol.bedrock.data.inventory.ItemData;
import org.cloudburstmc.protocol.bedrock.packet.*;
import org.cloudburstmc.protocol.common.DefinitionRegistry;
import org.cloudburstmc.protocol.common.PacketSignal;
import org.cloudburstmc.protocol.common.SimpleDefinitionRegistry;
import org.cloudburstmc.proxypass.ProxyPass;
import org.cloudburstmc.proxypass.network.bedrock.util.NbtBlockDefinitionRegistry;
import org.cloudburstmc.proxypass.network.bedrock.util.RecipeUtils;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.util.*;
import java.util.concurrent.*;
import java.util.stream.Collectors;

@Log4j2
@RequiredArgsConstructor
public class DownstreamPacketHandler implements BedrockPacketHandler {
    private final BedrockSession session;
    private final ProxyPlayerSession player;
    private final ProxyPass proxy;

    private final List<NbtMap> entityProperties = new ArrayList<>();

    // HashMap-based swing tracking (fixes race condition in multiplayer)
    // Key: Player runtime ID, Value: List of recent swings (up to 20 per player)
    private final Map<Long, List<SwingInfo>> playerSwings = new java.util.concurrent.ConcurrentHashMap<>();
    private static final int MAX_SWINGS_PER_PLAYER = 20;

    // Delayed HURT event processing (fixes packet ordering issues)
    private final ScheduledExecutorService delayedHurtExecutor = Executors.newSingleThreadScheduledExecutor();
    private final Set<Long> pendingHurtChecks = ConcurrentHashMap.newKeySet();
    private static final long DELAYED_CHECK_MS = 300; // Wait 300ms for swings to arrive

    // Swing information data class
    @lombok.Value
    private static class SwingInfo {
        long timestamp;
        org.cloudburstmc.math.vector.Vector3f position;
        org.cloudburstmc.math.vector.Vector3f rotation;
    }

    // Track player when they join the world
    @Override
    public PacketSignal handle(AddPlayerPacket packet) {
        player.getHitDetector().addPlayer(
            packet.getRuntimeEntityId(),
            packet.getUsername(),
            packet.getPosition(),
            packet.getRotation()
        );
        log.debug("Player added: {} (ID: {})", packet.getUsername(), packet.getRuntimeEntityId());
        return PacketSignal.UNHANDLED;
    }

    // Update player position when they move (from server to client)
    @Override
    public PacketSignal handle(MovePlayerPacket packet) {
        long runtimeId = packet.getRuntimeEntityId();
        long clientRuntimeId = player.getHitDetector().getClientRuntimeId();

        player.getHitDetector().updatePlayerPositionAndRotation(
            runtimeId,
            packet.getPosition(),
            packet.getRotation()
        );

        // Log only client position updates from server
        if (runtimeId == clientRuntimeId) {
            log.debug("Client position updated from DOWNSTREAM/server: ({}, {}, {})",
                String.format("%.2f", packet.getPosition().getX()),
                String.format("%.2f", packet.getPosition().getY()),
                String.format("%.2f", packet.getPosition().getZ()));
        }

        return PacketSignal.UNHANDLED;
    }

    // Track other players' movement (for other entities, server sends MoveEntityAbsolutePacket)
    @Override
    public PacketSignal handle(MoveEntityAbsolutePacket packet) {
        player.getHitDetector().updatePlayerPositionAndRotation(
            packet.getRuntimeEntityId(),
            packet.getPosition(),
            packet.getRotation()
        );
        return PacketSignal.UNHANDLED;
    }

    // Track animation (swing arm) which indicates attack
    @Override
    public PacketSignal handle(AnimatePacket packet) {
        if (packet.getAction() == AnimatePacket.Action.SWING_ARM) {
            long playerId = packet.getRuntimeEntityId();
            long timestamp = System.currentTimeMillis();

            // Get position and rotation at moment of swing
            org.cloudburstmc.math.vector.Vector3f position = player.getHitDetector().getPlayerPosition(playerId);
            org.cloudburstmc.math.vector.Vector3f rotation = player.getHitDetector().getPlayerRotation(playerId);

            if (position != null) {
                // Add swing to player's swing history
                playerSwings.computeIfAbsent(playerId, k -> new ArrayList<>());
                List<SwingInfo> swings = playerSwings.get(playerId);

                // Add new swing
                swings.add(new SwingInfo(timestamp, position, rotation));

                // Keep only last MAX_SWINGS_PER_PLAYER swings (circular buffer behavior)
                if (swings.size() > MAX_SWINGS_PER_PLAYER) {
                    swings.remove(0); // Remove oldest
                }

                log.debug("Player {} swung arm at position {} rotation {} (total swings tracked: {})",
                    playerId, position, rotation, swings.size());
            } else {
                log.warn("Position not available for player {} swing", playerId);
            }
        }
        return PacketSignal.UNHANDLED;
    }

    // Detect when client receives damage
    @Override
    public PacketSignal handle(EntityEventPacket packet) {
        // Check if this is HURT event
        if (packet.getType() == org.cloudburstmc.protocol.bedrock.data.entity.EntityEventType.HURT) {
            long victimId = packet.getRuntimeEntityId();
            long clientRuntimeId = player.getHitDetector().getClientRuntimeId();

            // IMPORTANT: Only process if the victim is the client
            if (victimId != clientRuntimeId) {
                return PacketSignal.UNHANDLED;
            }

            log.debug("Client received HURT event! victimId={}, clientId={}", victimId, clientRuntimeId);

            // Try to find attacker immediately
            processHurtEvent(false);
        }
        return PacketSignal.UNHANDLED;
    }

    // Process HURT event (immediate or delayed)
    private void processHurtEvent(boolean isDelayedCheck) {
        long clientRuntimeId = player.getHitDetector().getClientRuntimeId();
        long timestamp = System.currentTimeMillis();

        // Find best attacker using multi-criteria scoring
        AttackerCandidate bestAttacker = findBestAttacker();

        if (bestAttacker != null) {
            // Remove from pending checks if this was delayed
            pendingHurtChecks.remove(timestamp);

            log.info("Best attacker found{}: player {} with score {} (time={}ms, distance={}, angle={} deg)",
                isDelayedCheck ? " (delayed check)" : "",
                bestAttacker.playerId,
                String.format("%.3f", bestAttacker.totalScore),
                bestAttacker.timeSinceSwing,
                String.format("%.2f", bestAttacker.distance),
                String.format("%.1f", bestAttacker.aimAngle));

            player.getHitDetector().onHitReceived(
                bestAttacker.playerId,
                bestAttacker.swingPosition,
                bestAttacker.swingRotation
            );
        } else if (!isDelayedCheck) {
            // No attacker found on immediate check - schedule delayed check
            log.debug("No valid attacker found immediately, scheduling delayed check in {}ms", DELAYED_CHECK_MS);

            pendingHurtChecks.add(timestamp);
            delayedHurtExecutor.schedule(() -> {
                if (pendingHurtChecks.remove(timestamp)) {
                    log.debug("Executing delayed HURT check...");
                    processHurtEvent(true);
                }
            }, DELAYED_CHECK_MS, TimeUnit.MILLISECONDS);
        } else {
            // Delayed check also failed
            log.debug("No valid attacker found even after delayed check (no recent swings within time/distance limits)");
        }
    }

    // Multi-criteria scoring to find best attacker candidate
    private AttackerCandidate findBestAttacker() {
        long now = System.currentTimeMillis();
        long clientRuntimeId = player.getHitDetector().getClientRuntimeId();
        org.cloudburstmc.math.vector.Vector3f clientPosition = player.getHitDetector().getPlayerPosition(clientRuntimeId);

        if (clientPosition == null) {
            log.warn("Client position not available for attacker detection");
            return null;
        }

        log.debug("Finding attacker: client at position ({}, {}, {})",
            String.format("%.2f", clientPosition.getX()),
            String.format("%.2f", clientPosition.getY()),
            String.format("%.2f", clientPosition.getZ()));

        // Count total swings for debugging
        int totalSwings = 0;
        for (List<SwingInfo> swings : playerSwings.values()) {
            totalSwings += swings.size();
        }
        log.debug("Total players with swings: {}, total swing records: {}",
            playerSwings.size(), totalSwings);

        AttackerCandidate bestCandidate = null;
        double bestScore = 0.0;

        // Iterate through all players and their recent swings
        for (Map.Entry<Long, List<SwingInfo>> entry : playerSwings.entrySet()) {
            long playerId = entry.getKey();

            // Skip client's own swings
            if (playerId == clientRuntimeId) {
                continue;
            }

            List<SwingInfo> swings = entry.getValue();

            // Check each recent swing (most recent first)
            for (int i = swings.size() - 1; i >= 0; i--) {
                SwingInfo swing = swings.get(i);
                long timeSinceSwing = now - swing.timestamp;

                // Time window: 0-2500ms (no minimum delay - packets can arrive in any order in Bedrock)
                // Increased from 1500ms to catch more legitimate hits in laggy conditions
                if (timeSinceSwing > 2500) {
                    log.debug("Rejecting player {} swing: too old ({}ms > 2500ms)",
                        playerId, timeSinceSwing);
                    break; // Older swings will also be too old
                }
                // NOTE: No minimum time check - AnimatePacket can arrive almost simultaneously with HURT

                // Calculate distance
                double distance = calculateDistance(clientPosition, swing.position);

                // Distance limit: 15 blocks (extended for Bedrock Edition reach + lag compensation)
                // Increased from 10 to catch more legitimate hits in PvP combat
                if (distance > 15.0) {
                    log.debug("Rejecting player {} swing: too far ({} blocks > 15 blocks)",
                        playerId, String.format("%.2f", distance));
                    continue;
                }

                // Calculate aim angle
                double aimAngle = swing.rotation != null
                    ? calculateAimAngle(swing.position, swing.rotation, clientPosition)
                    : 90.0; // Default to 90 deg if rotation unavailable

                // Multi-criteria scoring (adjusted weights for better accuracy):
                // - Time: 30% weight, optimal at 100ms (reduced from 45%)
                // - Distance: 50% weight, closer is better (increased from 40%)
                // - Angle: 20% weight, smaller angle is better (increased from 15%)

                double timeScore = calculateTimeScore(timeSinceSwing);
                double distanceScore = calculateDistanceScore(distance);
                double angleScore = calculateAngleScore(aimAngle);

                double totalScore = (timeScore * 0.30) + (distanceScore * 0.50) + (angleScore * 0.20);

                log.debug("Candidate: player {} swing at T-{}ms, dist={}, angle={} deg → scores: time={}, dist={}, angle={}, TOTAL={}",
                    playerId, timeSinceSwing,
                    String.format("%.2f", distance),
                    String.format("%.1f", aimAngle),
                    String.format("%.3f", timeScore),
                    String.format("%.3f", distanceScore),
                    String.format("%.3f", angleScore),
                    String.format("%.3f", totalScore));

                if (totalScore > bestScore) {
                    bestScore = totalScore;
                    bestCandidate = new AttackerCandidate(
                        playerId, swing.position, swing.rotation, timeSinceSwing, distance, aimAngle, totalScore
                    );
                }
            }
        }

        // Return the best candidate even if score is low - better to show info than nothing
        // In laggy conditions or with poor aim, low scores can still be legitimate hits
        return bestCandidate;
    }

    // Calculate time score (optimal at 100ms)
    private double calculateTimeScore(long timeSinceSwing) {
        // Gaussian curve centered at 100ms
        double optimal = 100.0;
        double sigma = 150.0; // Spread
        double deviation = timeSinceSwing - optimal;
        return Math.exp(-(deviation * deviation) / (2 * sigma * sigma));
    }

    // Calculate distance score (closer is better, max 15 blocks)
    private double calculateDistanceScore(double distance) {
        // Linear: 0 blocks = 1.0, 15 blocks = 0.0
        return Math.max(0.0, 1.0 - (distance / 15.0));
    }

    // Calculate angle score (smaller angle is better, max 90 deg)
    private double calculateAngleScore(double aimAngle) {
        // Linear: 0 deg = 1.0, 90 deg = 0.0
        return Math.max(0.0, 1.0 - (aimAngle / 90.0));
    }

    // Calculate horizontal (XZ) distance between two positions
    // This is more accurate for PvP as it ignores height difference
    private double calculateDistance(org.cloudburstmc.math.vector.Vector3f pos1, org.cloudburstmc.math.vector.Vector3f pos2) {
        double dx = pos1.getX() - pos2.getX();
        double dz = pos1.getZ() - pos2.getZ();
        return Math.sqrt(dx * dx + dz * dz);
    }

    // Calculate aim angle between attacker's look direction and target
    private double calculateAimAngle(org.cloudburstmc.math.vector.Vector3f attackerPos,
                                     org.cloudburstmc.math.vector.Vector3f attackerRotation,
                                     org.cloudburstmc.math.vector.Vector3f targetPos) {
        float pitch = attackerRotation.getX();
        float yaw = attackerRotation.getY();

        double yawRad = Math.toRadians(yaw);
        double pitchRad = Math.toRadians(pitch);

        // Calculate look direction vector
        double lookX = -Math.sin(yawRad) * Math.cos(pitchRad);
        double lookY = -Math.sin(pitchRad);
        double lookZ = Math.cos(yawRad) * Math.cos(pitchRad);

        // Calculate direction to target
        double toTargetX = targetPos.getX() - attackerPos.getX();
        double toTargetY = targetPos.getY() - attackerPos.getY();
        double toTargetZ = targetPos.getZ() - attackerPos.getZ();

        // Normalize
        double targetLength = Math.sqrt(toTargetX * toTargetX + toTargetY * toTargetY + toTargetZ * toTargetZ);
        if (targetLength < 0.001) return 0.0;

        toTargetX /= targetLength;
        toTargetY /= targetLength;
        toTargetZ /= targetLength;

        // Dot product and angle
        double dotProduct = lookX * toTargetX + lookY * toTargetY + lookZ * toTargetZ;
        dotProduct = Math.max(-1.0, Math.min(1.0, dotProduct));

        return Math.toDegrees(Math.acos(dotProduct));
    }

    // Attacker candidate data class
    @lombok.Value
    private static class AttackerCandidate {
        long playerId;
        org.cloudburstmc.math.vector.Vector3f swingPosition;
        org.cloudburstmc.math.vector.Vector3f swingRotation;
        long timeSinceSwing;
        double distance;
        double aimAngle;
        double totalScore;
    }

    // Track weapon/item changes for players
    @Override
    public PacketSignal handle(MobEquipmentPacket packet) {
        // Track what item/weapon the player is holding
        ItemData item = packet.getItem();
        if (item != null && item.getDefinition() != null) {
            String itemIdentifier = item.getDefinition().getIdentifier();
            player.getHitDetector().updatePlayerWeapon(packet.getRuntimeEntityId(), itemIdentifier);
        }
        return PacketSignal.UNHANDLED;
    }

    @Override
    public PacketSignal handle(AvailableEntityIdentifiersPacket packet) {
        proxy.saveNBT("entity_identifiers", packet.getIdentifiers());
        return PacketSignal.UNHANDLED;
    }

    // Legacy - Versions prior to 1.21.80 (800) when client-side chunk generation is enabled
    @Override
    public PacketSignal handle(CompressedBiomeDefinitionListPacket packet) {
        proxy.saveNBT("biome_definitions_full", packet.getDefinitions());
        return PacketSignal.UNHANDLED;
    }

    @Override
    public PacketSignal handle(BiomeDefinitionListPacket packet) {
        if (packet.getDefinitions() != null) {
            // Legacy - Versions prior to 1.21.80 (800) when client-side chunk generation is disabled
            proxy.saveNBT("biome_definitions", packet.getDefinitions());
        }

        if (packet.getBiomes() != null) {
            Map<String, BiomeDefinitionData> definitions = packet.getBiomes().getDefinitions();
            Map<String, BiomeDefinitionData> strippedDefinitions = new LinkedHashMap<>();

            // Enable client-side chunk generation
            proxy.saveJson("biome_definitions.json", packet.getBiomes().getDefinitions());

            for (Map.Entry<String, BiomeDefinitionData> entry : definitions.entrySet()) {
                String id = entry.getKey();
                BiomeDefinitionData data = entry.getValue();

                strippedDefinitions.put(id, new BiomeDefinitionData(data.getId(), data.getTemperature(), data.getDownfall(), data.getFoliageSnow(), data.getDepth(), data.getScale(), data.getMapWaterColor(), data.isRain(), data.getTags(), null));
            }

            proxy.saveJson("stripped_biome_definitions.json", strippedDefinitions);
        }

        return PacketSignal.UNHANDLED;
    }

    @Override
    public PacketSignal handle(StartGamePacket packet) {
        // HIT DETECTOR: Set the client's runtime ID
        player.getHitDetector().setClientRuntimeId(packet.getRuntimeEntityId());
        log.info("Client runtime entity ID: {}", packet.getRuntimeEntityId());

        // HIT DETECTOR: Add client to players map with initial position
        String clientUsername = player.getIdentityData().displayName;
        org.cloudburstmc.math.vector.Vector3f initialPos = packet.getPlayerPosition();
        player.getHitDetector().addPlayer(
            packet.getRuntimeEntityId(),
            clientUsername,
            initialPos
        );
        log.info("Client added to HitDetector: {} at {}", clientUsername, initialPos);

        if (ProxyPass.CODEC.getProtocolVersion() < 776) {
            List<DataEntry> itemData = new ArrayList<>();

            LinkedHashMap<String, Integer> legacyItems = new LinkedHashMap<>();
            LinkedHashMap<String, Integer> legacyBlocks = new LinkedHashMap<>();

            for (ItemDefinition entry : packet.getItemDefinitions()) {
                if (entry.getRuntimeId() > 255) {
                    legacyItems.putIfAbsent(entry.getIdentifier(), entry.getRuntimeId());
                } else {
                    String id = entry.getIdentifier();
                    if (id.contains(":item.")) {
                        id = id.replace(":item.", ":");
                    }
                    if (entry.getRuntimeId() > 0) {
                        legacyBlocks.putIfAbsent(id, entry.getRuntimeId());
                    } else {
                        legacyBlocks.putIfAbsent(id, 255 - entry.getRuntimeId());
                    }
                }

                itemData.add(new DataEntry(entry.getIdentifier(), entry.getRuntimeId(), -1, false));
                ProxyPass.legacyIdMap.put(entry.getRuntimeId(), entry.getIdentifier());
            }

            SimpleDefinitionRegistry<ItemDefinition> itemDefinitions = SimpleDefinitionRegistry.<ItemDefinition>builder()
                    .addAll(packet.getItemDefinitions())
                    .add(new SimpleItemDefinition("minecraft:empty", 0, false))
                    .build();

            this.session.getPeer().getCodecHelper().setItemDefinitions(itemDefinitions);
            player.getUpstream().getPeer().getCodecHelper().setItemDefinitions(itemDefinitions);

            itemData.sort(Comparator.comparing(o -> o.name));

            proxy.saveJson("legacy_block_ids.json", sortMap(legacyBlocks));
            proxy.saveJson("legacy_item_ids.json", sortMap(legacyItems));
            proxy.saveJson("runtime_item_states.json", itemData);
        }


        DefinitionRegistry<BlockDefinition> registry;
        if (packet.isBlockNetworkIdsHashed()) {
            registry = this.proxy.getBlockDefinitionsHashed();
        } else {
            registry = this.proxy.getBlockDefinitions();
        }

        this.session.getPeer().getCodecHelper().setBlockDefinitions(registry);
        player.getUpstream().getPeer().getCodecHelper().setBlockDefinitions(registry);

        return PacketSignal.UNHANDLED;
    }

    @Override
    public PacketSignal handle(SyncEntityPropertyPacket packet) {
        entityProperties.add(packet.getData());
        NbtMapBuilder root = NbtMap.builder();
        entityProperties.forEach(map -> root.put(map.getString("type"), map));
        proxy.saveCompressedNBT("entity_properties", root.build());
        return PacketSignal.UNHANDLED;
    }

    @Override
    public PacketSignal handle(ItemComponentPacket packet) {
        List<DataEntry> itemData = new ArrayList<>();

        NbtMapBuilder root = NbtMap.builder();
        for (var item : packet.getItems()) {
            root.putCompound(item.getIdentifier(), item.getComponentData());
            itemData.add(new DataEntry(item.getIdentifier(), item.getRuntimeId(), item.getVersion().ordinal(), item.isComponentBased()));
        }

        if (ProxyPass.CODEC.getProtocolVersion() >= 776) {
            SimpleDefinitionRegistry.Builder<ItemDefinition> builder = SimpleDefinitionRegistry.<ItemDefinition>builder()
                    .add(new SimpleItemDefinition("minecraft:empty", 0, false));


            for (DataEntry entry : itemData) {
                ProxyPass.legacyIdMap.put(entry.getId(), entry.getName());
                builder.add(new SimpleItemDefinition(entry.getName(), entry.getId(), false));
            }

            SimpleDefinitionRegistry<ItemDefinition> itemDefinitions = builder.build();

            this.session.getPeer().getCodecHelper().setItemDefinitions(itemDefinitions);
            player.getUpstream().getPeer().getCodecHelper().setItemDefinitions(itemDefinitions);

            itemData.sort(Comparator.comparing(o -> o.name));
            proxy.saveJson("runtime_item_states.json", itemData);
        }

        proxy.saveCompressedNBT("item_components", root.build());

        return PacketSignal.UNHANDLED;
    }

    @Override
    public PacketSignal handle(CraftingDataPacket packet) {
        RecipeUtils.writeRecipes(packet, this.proxy);
        return PacketSignal.UNHANDLED;
    }

    @Override
    public PacketSignal handle(DisconnectPacket packet) {
        this.session.disconnect();
        // Let the client see the reason too.
        return PacketSignal.UNHANDLED;
    }

    private void dumpCreativeItems(List<CreativeItemGroup> groups, List<CreativeItemData> contents) {
        List<CreativeGroup> groupEntries = new ArrayList<>();
        for (CreativeItemGroup group : groups) {
            String categoryName = group.getCategory().name().toLowerCase();
            String name = group.getName();
            groupEntries.add(new CreativeGroup(name, categoryName, createCreativeItemEntry(group.getIcon())));
        }

        List<CreativeItemEntry> entries = new ArrayList<>();
        for (CreativeItemData content : contents) {
            entries.add(createCreativeItemEntry(content.getItem(), content.getGroupId()));
        }

        Map<String, Object> items = new HashMap<>();
        items.put("groups", groupEntries);
        items.put("items", entries);

        proxy.saveJson("creative_items.json", items);
    }

    private CreativeItemEntry createCreativeItemEntry(ItemData data, int groupId) {
        ItemEntry entry = createCreativeItemEntry(data);
        return new CreativeItemEntry(entry.getId(), entry.getDamage(), entry.getBlockRuntimeId(), entry.getBlockTag(), entry.getNbt(), groupId);
    }

    private ItemEntry createCreativeItemEntry(ItemData data) {
        ItemDefinition entry = data.getDefinition();
        String id = entry.getIdentifier();
        Integer damage = data.getDamage() == 0 ? null : (int) data.getDamage();

        String blockTag = null;
        Integer blockRuntimeId = null;
        if (data.getBlockDefinition() instanceof NbtBlockDefinitionRegistry.NbtBlockDefinition definition) {
            blockTag = encodeNbtToString(definition.tag());
        } else if (data.getBlockDefinition() != null) {
            blockRuntimeId = data.getBlockDefinition().getRuntimeId();
        }

        NbtMap tag = data.getTag();
        String tagData = null;
        if (tag != null) {
            tagData = encodeNbtToString(tag);
        }
        return new ItemEntry(id, damage, blockRuntimeId, blockTag, tagData);
    }

    @Override
    public PacketSignal handle(CreativeContentPacket packet) {
        try {
            dumpCreativeItems(packet.getGroups(), packet.getContents());
        } catch (Exception e) {
            log.error("Failed to dump creative contents", e);
        }
        return PacketSignal.UNHANDLED;
    }

    private static Map<String, Integer> sortMap(Map<String, Integer> map) {
        return map.entrySet().stream()
                .sorted(Map.Entry.comparingByKey())
                .collect(Collectors.toMap(
                        Map.Entry::getKey,
                        Map.Entry::getValue,
                        (oldValue, newValue) -> oldValue,
                        LinkedHashMap::new));
    }

    private static String encodeNbtToString(NbtMap tag) {
        try (ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream();
             NBTOutputStream stream = new NBTOutputStream(new LittleEndianDataOutputStream(byteArrayOutputStream))) {
            stream.writeTag(tag);
            return Base64.getEncoder().encodeToString(byteArrayOutputStream.toByteArray());
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    @Value
    @JsonInclude(JsonInclude.Include.NON_NULL)
    private static class CreativeItemEntry extends ItemEntry {
        private final int groupId;

        public CreativeItemEntry(String id, Integer damage, Integer blockRuntimeId, String blockTag, String nbt, int groupId) {
            super(id, damage, blockRuntimeId, blockTag, nbt);
            this.groupId = groupId;
        }
    }

    @Data
    @AllArgsConstructor
    @JsonInclude(JsonInclude.Include.NON_NULL)
    private static class ItemEntry {
        private final String id;
        private final Integer damage;
        private final Integer blockRuntimeId;
        @JsonProperty("block_state_b64")
        private final String blockTag;
        @JsonProperty("nbt_b64")
        private final String nbt;
    }

    @Value
    @JsonInclude(JsonInclude.Include.NON_NULL)
    private static class CreativeGroup {
        private final String name;
        private final String category;
        private final ItemEntry icon;
    }

    @Value
    private static class RuntimeEntry {
        private static final Comparator<RuntimeEntry> COMPARATOR = Comparator.comparingInt(RuntimeEntry::getId)
                .thenComparingInt(RuntimeEntry::getData);

        private final String name;
        private final int id;
        private final int data;
    }

    @Value
    private static class DataEntry {
        private final String name;
        private final int id;
        private final int version;
        private final boolean componentBased;
    }
}
