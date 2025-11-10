#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src/common/util/Rotation.hpp>
#include <mc/src/common/util/Mirror.hpp>
#include <mc/src/common/dataloadhelper/DataLoadHelperType.hpp>
#include <mc/src/common/world/Direction.hpp>

class InternalComponentRegistry {
public:
	class ComponentInfo;
};

class DataLoadHelper {
public:
    DataLoadHelper() = default;

	/// @vidx {0}
	MC virtual ~DataLoadHelper() = 0;

	/// @vidx {1}
	MC virtual Vec3 loadPosition(const Vec3& unk0) = 0;

	/// @vidx {2}
	MC virtual BlockPos loadBlockPosition(const BlockPos& unk0) = 0;

	/// @vidx {3}
	MC virtual BlockPos loadBlockPositionOffset(const BlockPos& unk0) = 0;

	/// @vidx {4}
	MC virtual float loadRotationDegreesX(float unk0) = 0;

	/// @vidx {5}
	MC virtual float loadRotationDegreesY(float unk0) = 0;

	/// @vidx {6}
	MC virtual float loadRotationRadiansX(float unk0) = 0;

	/// @vidx {7}
	MC virtual float loadRotationRadiansY(float unk0) = 0;

	/// @vidx {8}
	MC virtual unsigned char loadFacingID(unsigned char unk0) = 0;

	/// @vidx {9}
	MC virtual Vec3 loadDirection(const Vec3& unk0) = 0;

	/// @vidx {10}
	MC virtual Direction::Type loadDirection(Direction::Type unk0) = 0;

	/// @vidx {11}
	MC virtual Rotation loadRotation(Rotation unk0) = 0;

	/// @vidx {12}
	MC virtual Mirror loadMirror(Mirror unk0) = 0;

	/// @vidx {13}
	MC virtual ActorUniqueID loadActorUniqueID(ActorUniqueID unk0) = 0;

	/// @vidx {14}
	MC virtual ActorUniqueID loadOwnerID(ActorUniqueID unk0) = 0;

	/// @vidx {15}
	MC virtual const InternalComponentRegistry::ComponentInfo* loadActorInternalComponentInfo(const std::unordered_map<HashedString, InternalComponentRegistry::ComponentInfo>& unk0, const std::string& unk1) = 0;

	/// @vidx {16}
	MC virtual DataLoadHelperType getType() const= 0;

	/// @vidx {17}
	MC virtual bool shouldResetTime() = 0;
};