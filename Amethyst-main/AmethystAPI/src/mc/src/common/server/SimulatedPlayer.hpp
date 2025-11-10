#pragma once
#include <string>
#include <mc/src-deps/core/headerIncludes/gsl_includes.hpp>
#include <mc/src/common/server/ServerPlayer.hpp>
#include <mc/src/common/network/ServerNetworkHandler.hpp>

class BlockPos;

class SimulatedPlayer : public ServerPlayer {
public:
    /// @signature {48 89 5C 24 ? 55 56 57 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F9 41 8B D8 4C 8B F2 4C 8B C1}
    static SimulatedPlayer* create(
        const std::string& name, 
        const BlockPos& pos, 
        DimensionType dimension, 
        gsl::not_null<Bedrock::NonOwnerPointer<ServerNetworkHandler>> serverNetwork, 
        const std::string& xuid
    );

    void simulateDisconnect();
};