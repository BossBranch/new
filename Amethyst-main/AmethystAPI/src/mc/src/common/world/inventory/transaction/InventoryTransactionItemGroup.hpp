#pragma once
#include <memory>
#include <mc/src/common/nbt/CompoundTagVariant.hpp>
#include <mc/src/common/nbt/CompoundTag.hpp>

//class CompoundTag;

class InventoryTransactionItemGroup {
public:
    int mItemId;
    int mItemAux;
    std::unique_ptr<CompoundTag> mTag;
    int mCount;
    bool mOverflow;
};