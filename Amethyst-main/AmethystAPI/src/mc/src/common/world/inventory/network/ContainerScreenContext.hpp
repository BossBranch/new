#pragma once
#include <variant>
#include "mc/src/common/world/Container.hpp"
#include "mc/src/common/ActorUniqueID.hpp"
#include "mc/src/common/world/level/BlockPos.hpp"

class Player;

class ContainerScreenContext {
public:
    Player* mPlayer;
    ContainerType mScreenContainerType;
    std::variant<std::monostate, ActorUniqueID, BlockPos> mOwner;

    ContainerScreenContext(Player* player, ContainerType type) : 
        mPlayer(player),
        mScreenContainerType(type), 
        mOwner(std::monostate{}) {}

    ContainerScreenContext(const ContainerScreenContext&) = default;
    ContainerScreenContext& operator=(const ContainerScreenContext& other) {
        if (this != &other) {
            mPlayer = other.mPlayer;
            mScreenContainerType = other.mScreenContainerType;
            mOwner = other.mOwner;
        }
        return *this;
    }
};