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
    private final Map<Long, String> playerWeapons = new ConcurrentHashMap<>();

    // Thorns detection: track client's recent attacks
    private Long lastClientAttackTime = null;
    private Long lastClientAttackTarget = null;

    private long clientRuntimeId = 0;

    // Time window for Thorns detection (milliseconds) - based on research
    private static final long THORNS_DETECTION_WINDOW = 100;

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

        // Clear client attack tracking if this was the target
        if (lastClientAttackTarget != null && lastClientAttackTarget == runtimeId) {
            lastClientAttackTime = null;
            lastClientAttackTarget = null;
            log.debug("Cleared client attack tracking for removed player: {}", runtimeId);
        }

        log.debug("Player removed from tracking: {}", runtimeId);
    }

    /**
     * Record when client attacks an entity
     * Used to detect thorns damage
     */
    public void recordClientAttack(long targetRuntimeId) {
        lastClientAttackTime = System.currentTimeMillis();
        lastClientAttackTarget = targetRuntimeId;
        log.debug("Client attacked entity: {} at time: {}", targetRuntimeId, lastClientAttackTime);
    }

    /**
     * Update player's equipped weapon
     */
    public void updatePlayerWeapon(long runtimeId, String itemIdentifier) {
        playerWeapons.put(runtimeId, itemIdentifier);
        log.debug("Player {} weapon updated: {}", runtimeId, itemIdentifier);
    }

    /**
     * Check if damage is from Thorns enchantment
     * Based on PDF research: Thorns damage occurs 10-100ms AFTER client attacks,
     * without InventoryTransactionPacket or AnimatePacket from the victim
     */
    private boolean isThornsHit(long attackerRuntimeId) {
        // Did client attack someone recently?
        if (lastClientAttackTime == null || lastClientAttackTarget == null) {
            return false;
        }

        long now = System.currentTimeMillis();
        long timeSinceClientAttack = now - lastClientAttackTime;

        // Check if:
        // 1. Client attacked someone within THORNS_DETECTION_WINDOW (100ms)
        // 2. The "attacker" is the same entity that client attacked
        if (timeSinceClientAttack < THORNS_DETECTION_WINDOW &&
            attackerRuntimeId == lastClientAttackTarget) {

            String attackerName = getPlayerUsername(attackerRuntimeId);
            log.info("Thorns damage detected from: {} (client attacked them {}ms ago)",
                attackerName, timeSinceClientAttack);

            // Clear the attack record
            lastClientAttackTime = null;
            lastClientAttackTarget = null;

            return true;
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
            aimInfo = String.format(" [%.1f deg]", aimAngle);
            log.debug("Calculated aim angle: {} deg", aimAngle);
        } else {
            log.warn("Attacker rotation not available for ID: {}", attackerRuntimeId);
        }

        // Get attacker's weapon
        String weapon = playerWeapons.get(attackerRuntimeId);
        String weaponInfo = "";
        if (weapon != null && !weapon.equals("minecraft:air")) {
            // Remove minecraft: prefix and make readable
            String weaponName = weapon.replace("minecraft:", "").replace("_", " ");
            weaponInfo = String.format(" [%s]", weaponName);
        }

        // Send message to client chat
        String message = String.format("[HIT] %s hit you from %.2f blocks%s%s",
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
            System.out.println("Aim Angle: " + String.format("%.1f", aimAngle) + " deg (0 deg = perfect aim)");
        }
        System.out.println("==================================");

        log.info("Hit detected: {} -> client from {} blocks with {} at {} deg angle (attacker pos: {}, client pos: {})",
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
     * 0 deg = perfect aim, higher = worse aim
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
     * Sends both SYSTEM message (chat) and TIP message (action bar) for maximum visibility
     */
    private void sendChatMessage(String message) {
        // Method 1: System message in chat
        TextPacket systemPacket = new TextPacket();
        systemPacket.setType(TextPacket.Type.SYSTEM);
        systemPacket.setNeedsTranslation(false);
        systemPacket.setMessage(message);
        systemPacket.setSourceName("");
        systemPacket.setXuid("");
        systemPacket.setPlatformChatId("");
        session.getUpstream().sendPacket(systemPacket);

        // Method 2: Tip message (action bar above hotbar) for important alerts
        // This is more visible and doesn't clutter chat
        TextPacket tipPacket = new TextPacket();
        tipPacket.setType(TextPacket.Type.TIP);
        tipPacket.setNeedsTranslation(false);
        tipPacket.setMessage(message);
        tipPacket.setXuid("");
        tipPacket.setPlatformChatId("");
        session.getUpstream().sendPacket(tipPacket);

        log.debug("Chat message sent to client (SYSTEM + TIP): {}", message);
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
