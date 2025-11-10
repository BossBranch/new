/// @symbols
#pragma once
#include <cstdint>
#include <mc/src/common/dataloadhelper/DataLoadHelper.hpp>

/// @vptr {0x4D79138}
class DefaultDataLoadHelper : public DataLoadHelper {
public:
    DefaultDataLoadHelper() = default;

	/// @vidx {0}
	MC virtual ~DefaultDataLoadHelper() override;

	/// @vidx {1}
	MC virtual Vec3 loadPosition(const Vec3& unk0) override;

	/// @vidx {2}
	MC virtual BlockPos loadBlockPosition(const BlockPos& unk0) override;

	/// @vidx {3}
	MC virtual BlockPos loadBlockPositionOffset(const BlockPos& unk0) override;

	/// @vidx {4}
	MC virtual float loadRotationDegreesX(float unk0) override;

	/// @vidx {5}
	MC virtual float loadRotationDegreesY(float unk0) override;

	/// @vidx {6}
	MC virtual float loadRotationRadiansX(float unk0) override;

	/// @vidx {7}
	MC virtual float loadRotationRadiansY(float unk0) override;

	/// @vidx {8}
	MC virtual unsigned char loadFacingID(unsigned char unk0) override;

	/// @vidx {10}
	MC virtual Vec3 loadDirection(const Vec3& unk0) override;

	/// @vidx {9}
	MC virtual Direction::Type loadDirection(Direction::Type unk0) override;

	/// @vidx {11}
	MC virtual Rotation loadRotation(Rotation unk0) override;

	/// @vidx {12}
	MC virtual Mirror loadMirror(Mirror unk0) override;

	/// @vidx {13}
	MC virtual ActorUniqueID loadActorUniqueID(ActorUniqueID unk0) override;

	/// @vidx {14}
	MC virtual ActorUniqueID loadOwnerID(ActorUniqueID unk0) override;

	/// @vidx {15}
	MC virtual const InternalComponentRegistry::ComponentInfo* loadActorInternalComponentInfo(const std::unordered_map<HashedString, InternalComponentRegistry::ComponentInfo, std::hash<HashedString>, std::equal_to<HashedString>, std::allocator<std::pair<const HashedString, InternalComponentRegistry::ComponentInfo>>>& unk0, const std::string& unk1) override;

	/// @vidx {16}
	MC virtual DataLoadHelperType getType() const override;

	/// @vidx {17}
	MC virtual bool shouldResetTime() override;
};