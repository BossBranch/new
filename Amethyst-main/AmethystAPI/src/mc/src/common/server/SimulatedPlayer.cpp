#include "SimulatedPlayer.hpp"

SimulatedPlayer* SimulatedPlayer::create(const std::string& name, const BlockPos& pos, DimensionType dimension, gsl::not_null<Bedrock::NonOwnerPointer<ServerNetworkHandler>> serverNetwork, const std::string& xuid)
{
    using function = decltype(&SimulatedPlayer::create);
    static auto func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 55 56 57 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F9 41 8B D8 4C 8B F2 4C 8B C1"));
    return func(name, pos, dimension, serverNetwork, xuid);
}

void SimulatedPlayer::simulateDisconnect()
{
    // this is actually calling MinecraftGameTestHelper::removeSimulatedPlayer(class SimulatedPlayer & __ptr64) __ptr64
    // ^ this func just directly calls simulateDisconnect, but it got inlined.

    using function = void(*)(void*, void*);
    static auto func = std::bit_cast<function>(SigScan("40 53 48 83 EC ? 48 8B CA 48 8B DA E8 ? ? ? ? 48 8B 03"));
    return func(nullptr, this);
}