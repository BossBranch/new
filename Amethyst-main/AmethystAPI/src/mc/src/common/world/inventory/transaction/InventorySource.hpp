#pragma once
#include "mc/src/common/world/actor/player/PlayerInventory.hpp"

enum class InventorySourceType : uint32_t {
    InvalidInventory = 0xFFFFFFFF,
    ContainerInventory = 0x0,
    GlobalInventory = 0x1,
    WorldInteraction = 0x2,
    CreativeInventory = 0x3,
    NonImplementedFeatureTODO = 0x1869F,
};

class InventorySource {
public:
    enum class InventorySourceFlags : int32_t {
        NoFlag = 0x0,
        WorldInteraction_Random = 0x1,
    };

    InventorySourceType mType;
	ContainerID mContainerId;
	InventorySourceFlags mFlags;

    InventorySource(InventorySourceType type, ContainerID container, InventorySourceFlags flags) : 
        mType(type), mContainerId(container), mFlags(flags) {}

    InventorySource(const InventorySource& other) {
        this->mType = other.mType;
        this->mContainerId = other.mContainerId;
        this->mFlags = other.mFlags;
    }

    bool operator==(const InventorySource& other) const {
        return this->mType == other.mType && this->mContainerId == other.mContainerId && this->mFlags == other.mFlags;
    }
};

namespace std {
template <>
struct hash<InventorySource> {
    size_t operator()(const InventorySource& source) const
    {
        return (static_cast<size_t>(source.mType) << 32) | (static_cast<size_t>(source.mContainerId) << 16) | static_cast<size_t>(source.mFlags);
    }
};
} // namespace std