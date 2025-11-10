#include "FillingContainer.hpp"

#include "mc/src/common/world/item/ItemStack.hpp"

FillingContainer::FillingContainer(Player* player, int size, ContainerType type) : Container(type),
    mPlayer(player)
{
    mItems.resize(size);
}