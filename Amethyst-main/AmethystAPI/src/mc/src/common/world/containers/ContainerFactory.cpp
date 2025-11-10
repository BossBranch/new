#include "ContainerFactory.hpp"
#include "mc/src/common/world/Container.hpp"
#include "mc/src/common/world/actor/player/PlayerInventory.hpp"
#include "mc/src/common/world/actor/player/Player.hpp"

void ContainerFactory::_setPlayerContainerManagerModel(Player& player, std::shared_ptr<IContainerManager> manager)
{
    player.setContainerManagerModel(manager);
}

std::weak_ptr<IContainerManager> ContainerFactory::_getPlayerContainerManagerModel(const Player& player)
{
    return player.getContainerManagerModel();
}
