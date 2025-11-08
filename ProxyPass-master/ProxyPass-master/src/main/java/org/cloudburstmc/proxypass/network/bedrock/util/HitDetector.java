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
    }

    /**
     * Track new player
     */
    public void addPlayer(long runtimeId, String username, Vector3f position) {
        players.put(runtimeId, new PlayerInfo(username, position));
        log.debug("Player tracked: {} (ID: {}) at {}", username, runtimeId, position);
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
     * Get player position
     */
    public Vector3f getPlayerPosition(long runtimeId) {
        PlayerInfo info = players.get(runtimeId);
        return info != null ? info.getPosition() : null;
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
        // Check if this is thorns damage (we recently attacked this entity)
        if (isThornsHit(attackerRuntimeId)) {
            String attackerName = getPlayerUsername(attackerRuntimeId);
            log.info("Thorns damage ignored from: {}", attackerName);
            // Optionally show thorns message
            // sendChatMessage(String.format("§6[THORNS] §7%s", attackerName));
            return;
        }

        // Get client position
        PlayerInfo clientInfo = players.get(clientRuntimeId);
        if (clientInfo == null) {
            log.warn("Client position not tracked yet");
            return;
        }
        Vector3f clientPosition = clientInfo.getPosition();

        // Get attacker info
        String attackerName = getPlayerUsername(attackerRuntimeId);
        Vector3f trackedAttackerPosition = getPlayerPosition(attackerRuntimeId);

        // Use tracked position if available, otherwise use position from packet
        Vector3f actualAttackerPosition = trackedAttackerPosition != null ? trackedAttackerPosition : attackerPosition;

        // Calculate distance
        double distance = calculateDistance(clientPosition, actualAttackerPosition);

        // Get attacker's weapon
        String weapon = playerWeapons.get(attackerRuntimeId);
        String weaponInfo = "";
        if (weapon != null && !weapon.equals("minecraft:air")) {
            // Remove minecraft: prefix and make readable
            String weaponName = weapon.replace("minecraft:", "").replace("_", " ");
            weaponInfo = String.format(" §8[§e%s§8]", weaponName);
        }

        // Send message to client chat
        sendChatMessage(String.format("§c[HIT] §f%s§7 hit you from §e%.2f§7 blocks%s",
            attackerName, distance, weaponInfo));

        log.info("Hit detected: {} -> client from {} blocks with {} (attacker pos: {}, client pos: {})",
            attackerName, distance, weapon, actualAttackerPosition, clientPosition);
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

        public PlayerInfo(String username, Vector3f position) {
            this.username = username;
            this.position = position;
        }
    }
}
