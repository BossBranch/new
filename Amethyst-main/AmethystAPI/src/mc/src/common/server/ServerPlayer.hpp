/// @symbols
#pragma once
#include <mc/src/common/world/actor/player/Player.hpp>

class FurnaceContainerManagerModel;
class ServerPlayer : public Player {
public:
    std::byte padding7584[152];
    char mContainerCounter;

    ContainerID nextContainerId() {
        auto nextContainerId = mContainerCounter + 1;
        if (nextContainerId >= (char)ContainerID::CONTAINER_ID_LAST)
            nextContainerId = (char)ContainerID::CONTAINER_ID_FIRST;
        mContainerCounter = nextContainerId;
        return ContainerID(nextContainerId);
    }

	template<typename TContainer, typename... TArgs>
	void openManagedContainer(TArgs&&... args) {
		static_assert(sizeof(TContainer) == 0, "openManagerContainer for TContainer not implemented.");
	}

	/** @address {0x4037CC0} */
	template<>
	MC void openManagedContainer<FurnaceContainerManagerModel>(const BlockPos& pos);
};

static_assert(offsetof(ServerPlayer, mContainerCounter) == 7744);