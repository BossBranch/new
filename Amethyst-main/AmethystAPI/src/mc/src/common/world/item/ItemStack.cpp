#include "mc/src/common/world/item/ItemStack.hpp"
#include "mc/src/common/world/item/Item.hpp"

ItemStack::ItemStack() : 
    ItemStackBase() 
{    
}

ItemStack::ItemStack(const ItemStack& other) : 
    ItemStackBase(other),
    mNetIdVariant(other.mNetIdVariant)
{
}

int ItemStack::getMaxUseDuration() const
{
    if (mItem)
        return mItem->getMaxUseDuration(this);
    return 0;
}