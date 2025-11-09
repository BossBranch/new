package org.cloudburstmc.proxypass.network.bedrock.util;

import lombok.Data;
import lombok.extern.log4j.Log4j2;
import org.cloudburstmc.math.vector.Vector3f;
import org.cloudburstmc.protocol.bedrock.packet.TextPacket;
import org.cloudburstmc.proxypass.network.bedrock.session.ProxyPlayerSession;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

/**
 * Client-side hit detector (anti-cheat)
 * Tracks player positions and detects hits with distance calculation
 */
@Log4j2
public class HitDetector {

    private final ProxyPlayerSession session;
    private final Map<Long, PlayerInfo> players = new ConcurrentHashMap<>();
    private final Map<Long, Long> recentClientAttacks = new ConcurrentHashMap<>();
    private final Map<Long, String> playerWeapons = new ConcurrentHashMap<>();
    private long clientRuntimeId = 0;

    // Time window to ignore thorns damage after client attack (milliseconds)
    private static final long THORNS_IGNORE_WINDOW = 300;

    public HitDetector(ProxyPlayerSession session) {
        this.session = session;
    }

    /**
     * Register client's runtime entity ID
     */
    public void setClientRuntimeId(long runtimeId) {
        this.clientRuntimeId = runtimeId;
        log.info("Client runtime ID set to: {}", runtimeId);

        // Add client to players map with initial position from StartGamePacket
        // Position will be updated later via MovePlayerPacket
    }

    /**
     * Get client's runtime entity ID
     */
    public long getClientRuntimeId() {
        return clientRuntimeId;
    }

    /**
     * Track new player
     */
    public void addPlayer(long runtimeId, String username, Vector3f position) {
        players.put(runtimeId, new PlayerInfo(username, position));
        log.debug("Player tracked: {} (ID: {}) at {}", username, runtimeId, position);
    }

    public void addPlayer(long runtimeId, String username, Vector3f position, Vector3f rotation) {
        players.put(runtimeId, new PlayerInfo(username, position, rotation));
        log.debug("Player tracked: {} (ID: {}) at {} rotation {}", username, runtimeId, position, rotation);
    }

    /**
     * Update player position
     */
    public void updatePlayerPosition(long runtimeId, Vector3f position) {
        PlayerInfo info = players.get(runtimeId);
        if (info != null) {
            info.setPosition(position);
        }
    }

    /**
     * Update player position and rotation
     */
    public void updatePlayerPositionAndRotation(long runtimeId, Vector3f position, Vector3f rotation) {
        PlayerInfo info = players.get(runtimeId);
        if (info != null) {
            info.setPosition(position);
            info.setRotation(rotation);
        }
    }

    /**
     * Get player position
     */
    public Vector3f getPlayerPosition(long runtimeId) {
        PlayerInfo info = players.get(runtimeId);
        return info != null ? info.getPosition() : null;
    }

    /**
     * Get player rotation (pitch, yaw, headYaw)
     */
    public Vector3f getPlayerRotation(long runtimeId) {
        PlayerInfo info = players.get(runtimeId);
        return info != null ? info.getRotation() : null;
    }

    /**
     * Get player username
     */
    public String getPlayerUsername(long runtimeId) {
        PlayerInfo info = players.get(runtimeId);
        return info != null ? info.getUsername() : "Unknown";
    }

    /**
     * Remove player from tracking
     */
    public void removePlayer(long runtimeId) {
        players.remove(runtimeId);
        playerWeapons.remove(runtimeId);
        recentClientAttacks.remove(runtimeId);
        log.debug("Player removed from tracking: {}", runtimeId);
    }

    /**
     * Record when client attacks an entity
     * Used to detect thorns damage
     */
    public void recordClientAttack(long targetRuntimeId) {
        recentClientAttacks.put(targetRuntimeId, System.currentTimeMillis());
        log.debug("Client attacked entity: {}", targetRuntimeId);
    }

    /**
     * Update player's equipped weapon
     */
    public void updatePlayerWeapon(long runtimeId, String itemIdentifier) {
        playerWeapons.put(runtimeId, itemIdentifier);
        log.debug("Player {} weapon updated: {}", runtimeId, itemIdentifier);
    }

    /**
     * Check if damage is likely from thorns (client recently attacked this entity)
     */
    private boolean isThornsHit(long attackerRuntimeId) {
        Long lastAttackTime = recentClientAttacks.get(attackerRuntimeId);
        if (lastAttackTime != null) {
            long timeSinceAttack = System.currentTimeMillis() - lastAttackTime;
            if (timeSinceAttack < THORNS_IGNORE_WINDOW) {
                // This is thorns damage - remove from tracking
                recentClientAttacks.remove(attackerRuntimeId);
                return true;
            }
        }
        return false;
    }

    /**
     * Called when someone attacks the client
     *
     * @param attackerRuntimeId The attacker's runtime entity ID
     * @param attackerPosition The position where attack originated (from packet)
     */
    public void onHitReceived(long attackerRuntimeId, Vector3f attackerPosition) {
        log.debug("onHitReceived called! attackerId={}, position={}", attackerRuntimeId, attackerPosition);

        // Check if this is thorns damage (we recently attacked this entity)
        if (isThornsHit(attackerRuntimeId)) {
            String attackerName = getPlayerUsername(attackerRuntimeId);
            log.info("Thorns damage ignored from: {}", attackerName);
            // Optionally show thorns message
            // sendChatMessage(String.format("§6[THORNS] §7%s", attackerName));
            return;
        }

        // Get client position
        log.debug("Getting client position for ID: {}", clientRuntimeId);
        log.debug("Players map size: {}, contains client: {}", players.size(), players.containsKey(clientRuntimeId));

        PlayerInfo clientInfo = players.get(clientRuntimeId);
        if (clientInfo == null) {
            log.warn("Client position not tracked yet! clientId={}, playersMap={}", clientRuntimeId, players.keySet());
            return;
        }
        Vector3f clientPosition = clientInfo.getPosition();
        log.debug("Client position: {}", clientPosition);

        // Get attacker info
        String attackerName = getPlayerUsername(attackerRuntimeId);
        Vector3f trackedAttackerPosition = getPlayerPosition(attackerRuntimeId);
        log.debug("Attacker name: {}, tracked position: {}", attackerName, trackedAttackerPosition);

        // Use tracked position if available, otherwise use position from packet
        Vector3f actualAttackerPosition = trackedAttackerPosition != null ? trackedAttackerPosition : attackerPosition;

        // Calculate distance
        double distance = calculateDistance(clientPosition, actualAttackerPosition);
        log.debug("Calculated distance: {} blocks", distance);

        // Calculate aim angle (crosshair offset)
        Vector3f attackerRotation = getPlayerRotation(attackerRuntimeId);
        double aimAngle = -1.0;
        String aimInfo = "";
        if (attackerRotation != null) {
            aimAngle = calculateAimAngle(actualAttackerPosition, attackerRotation, clientPosition);
            aimInfo = String.format(" §8[§6%.1f°§8]", aimAngle);
            log.debug("Calculated aim angle: {}°", aimAngle);
        } else {
            log.warn("Attacker rotation not available for ID: {}", attackerRuntimeId);
        }

        // Filter out impossible hits (potions, thorns, fire damage, etc.)
        // Maximum realistic distance: 10 blocks (considering lag/ping)
        // Maximum realistic aim angle: 45 degrees (player must be looking at target)
        final double MAX_HIT_DISTANCE = 10.0;
        final double MAX_AIM_ANGLE = 45.0;

        if (distance > MAX_HIT_DISTANCE) {
            log.info("Ignored hit from {} at {} blocks (too far, likely potion/thorns/fire damage)",
                attackerName, String.format("%.2f", distance));
            return;
        }

        if (aimAngle >= 0 && aimAngle > MAX_AIM_ANGLE) {
            log.info("Ignored hit from {} with {}° aim angle (not looking at target, likely potion/thorns/fire damage)",
                attackerName, String.format("%.1f", aimAngle));
            return;
        }

        // Get attacker's weapon
        String weapon = playerWeapons.get(attackerRuntimeId);
        String weaponInfo = "";
        if (weapon != null && !weapon.equals("minecraft:air")) {
            // Remove minecraft: prefix and make readable
            String weaponName = weapon.replace("minecraft:", "").replace("_", " ");
            weaponInfo = String.format(" §8[§e%s§8]", weaponName);
        }

        // Send message to client chat
        String message = String.format("§c[HIT] §f%s§7 hit you from §e%.2f§7 blocks%s%s",
            attackerName, distance, weaponInfo, aimInfo);
        log.info("Sending hit message to client: {}", message);
        sendChatMessage(message);

        // Also log to console
        System.out.println("==================================");
        System.out.println("[HIT DETECTED]");
        System.out.println("Attacker: " + attackerName + " (ID: " + attackerRuntimeId + ")");
        System.out.println("Distance: " + String.format("%.2f", distance) + " blocks");
        System.out.println("Weapon: " + (weapon != null ? weapon : "unknown"));
        if (aimAngle >= 0) {
            System.out.println("Aim Angle: " + String.format("%.1f", aimAngle) + "° (0° = perfect aim)");
        }
        System.out.println("==================================");

        log.info("Hit detected: {} -> client from {} blocks with {} at {}° angle (attacker pos: {}, client pos: {})",
            attackerName, distance, weapon, aimAngle >= 0 ? String.format("%.1f", aimAngle) : "N/A",
            actualAttackerPosition, clientPosition);
    }

    /**
     * Calculate 3D distance between two positions
     */
    private double calculateDistance(Vector3f pos1, Vector3f pos2) {
        double dx = pos1.getX() - pos2.getX();
        double dy = pos1.getY() - pos2.getY();
        double dz = pos1.getZ() - pos2.getZ();
        return Math.sqrt(dx * dx + dy * dy + dz * dz);
    }

    /**
     * Calculate aim angle (crosshair offset) in degrees
     * Returns the angle between attacker's look direction and direction to target
     * 0° = perfect aim, higher = worse aim
     */
    private double calculateAimAngle(Vector3f attackerPos, Vector3f attackerRotation, Vector3f targetPos) {
        // Get pitch and yaw from rotation (rotation = pitch, yaw, headYaw)
        float pitch = attackerRotation.getX();
        float yaw = attackerRotation.getY();

        // Convert to radians
        double yawRad = Math.toRadians(yaw);
        double pitchRad = Math.toRadians(pitch);

        // Calculate look direction vector from pitch and yaw
        double lookX = -Math.sin(yawRad) * Math.cos(pitchRad);
        double lookY = -Math.sin(pitchRad);
        double lookZ = Math.cos(yawRad) * Math.cos(pitchRad);

        // Calculate direction to target
        double toTargetX = targetPos.getX() - attackerPos.getX();
        double toTargetY = targetPos.getY() - attackerPos.getY();
        double toTargetZ = targetPos.getZ() - attackerPos.getZ();

        // Normalize toTarget vector
        double targetLength = Math.sqrt(toTargetX * toTargetX + toTargetY * toTargetY + toTargetZ * toTargetZ);
        if (targetLength < 0.001) return 0.0; // Avoid division by zero

        toTargetX /= targetLength;
        toTargetY /= targetLength;
        toTargetZ /= targetLength;

        // Calculate dot product
        double dotProduct = lookX * toTargetX + lookY * toTargetY + lookZ * toTargetZ;

        // Clamp dot product to [-1, 1] to avoid NaN from acos
        dotProduct = Math.max(-1.0, Math.min(1.0, dotProduct));

        // Calculate angle in degrees
        double angleRad = Math.acos(dotProduct);
        return Math.toDegrees(angleRad);
    }

    /**
     * Send chat message to client
     */
    private void sendChatMessage(String message) {
        TextPacket textPacket = new TextPacket();
        textPacket.setType(TextPacket.Type.RAW);
        textPacket.setNeedsTranslation(false);
        textPacket.setMessage(message);
        textPacket.setXuid("");
        textPacket.setPlatformChatId("");

        // Send to client (upstream)
        session.getUpstream().sendPacket(textPacket);
    }

    /**
     * Player info storage
     */
    @Data
    private static class PlayerInfo {
        private final String username;
        private Vector3f position;
        private Vector3f rotation; // pitch, yaw, headYaw

        public PlayerInfo(String username, Vector3f position, Vector3f rotation) {
            this.username = username;
            this.position = position;
            this.rotation = rotation != null ? rotation : Vector3f.ZERO;
        }

        // Convenience constructor for backward compatibility
        public PlayerInfo(String username, Vector3f position) {
            this(username, position, Vector3f.ZERO);
        }
    }
}
