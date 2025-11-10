/// @symbols
#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src-deps/core/utility/AutomaticID.hpp>

struct ActorUniqueID;
class Vec3;
class BiomeRegistry;
class BlockPos;
class Packet;
class Player;
class Actor;

/// @vptr {0x4CB1400}
class IDimension {
public:
	/// @vidx {0}
    MC virtual ~IDimension() = default;

	/// @vidx {1}
    MC virtual bool isNaturalDimension() const = 0;

	/// @vidx {2}
    MC virtual DimensionType getDimensionId() const = 0;

	/// @vidx {3}
    MC virtual void sendPacketForPosition(const BlockPos&, const Packet&, const Player*) = 0;

	/// @vidx {4}
    MC virtual void flushLevelChunkGarbageCollector() = 0;
	
	/// @vidx {5}
    MC virtual void initializeWithLevelStorageManager(class LevelStorageManager&) = 0;
	
	/// @vidx {6}
    MC virtual BiomeRegistry& getBiomeRegistry() = 0;
	
	/// @vidx {7}
    MC virtual const BiomeRegistry& getBiomeRegistry() const = 0;
	
	/// @vidx {8}
    MC virtual Vec3 translatePosAcrossDimension(const Vec3&, DimensionType) const = 0;
	
	/// @vidx {9}
    MC virtual void forEachPlayer(std::function<bool(class Player&)> callback) const = 0;
	
	/// @vidx {10}
    MC virtual Actor* fetchEntity(ActorUniqueID actorID, bool getRemoved) const = 0;
};