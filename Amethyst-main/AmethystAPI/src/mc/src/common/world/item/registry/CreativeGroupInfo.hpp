#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src/common/world/item/CreativeItemCategory.hpp>
#include <mc/src/common/world/item/ItemInstance.hpp>

class CreativeItemRegistry;

class CreativeGroupInfo : Bedrock::EnableNonOwnerReferences {
public:
    CreativeItemCategory mCategory;
    CreativeItemRegistry* mRegistry;
    HashedString mName;
    ItemInstance mIcon;
    unsigned int mIndex;
    std::vector<unsigned int> mItemIndexes;
};