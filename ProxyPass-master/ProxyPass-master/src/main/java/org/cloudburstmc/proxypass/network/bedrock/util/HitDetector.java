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
    private long clientRuntimeId = 0;

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
        log.debug("Player removed from tracking: {}", runtimeId);
    }

    /**
     * Called when someone attacks the client
     *
     * @param attackerRuntimeId The attacker's runtime entity ID
     * @param attackerPosition The position where attack originated (from packet)
     */
    public void onHitReceived(long attackerRuntimeId, Vector3f attackerPosition) {
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

        // Send message to client chat
        sendChatMessage(String.format("§c[HIT] §f%s §7hit you from §e%.2f §7blocks",
            attackerName, distance));

        log.info("Hit detected: {} -> client from {} blocks (attacker pos: {}, client pos: {})",
            attackerName, distance, actualAttackerPosition, clientPosition);
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
