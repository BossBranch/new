/// @symbolgeneration
#pragma once
#include "amethyst/Imports.hpp"
#include <string>
#include "mc/src/common/world/item/ItemDescriptorCount.hpp"
#include "mc/src/common/CommonTypes.hpp"
#include "mc/src/common/world/inventory/network/ItemStackNetIdVariant.hpp"

class ItemStack;

class NetworkItemStackDescriptor : public ItemDescriptorCount {
public:
	bool mIncludeNetIds;
	ItemStackNetIdVariant mNetIdVariant;
	BlockRuntimeId mBlockRuntimeId;
	std::string mUserDataBuffer;

	/// @signature {48 89 5C 24 ? 55 56 57 41 56 41 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8B FA 48 8B F1 48 89 4C 24 ? 0F B6 5A}
	MC NetworkItemStackDescriptor(const ItemStack& stack);

	NetworkItemStackDescriptor operator=(const NetworkItemStackDescriptor& other) {
        if (this != &other) {
            ItemDescriptorCount::operator=(other);
            this->mIncludeNetIds = other.mIncludeNetIds;
            this->mNetIdVariant = other.mNetIdVariant;
            this->mBlockRuntimeId = other.mBlockRuntimeId;
            this->mUserDataBuffer = other.mUserDataBuffer;
		}
            
        return *this;
	}
};