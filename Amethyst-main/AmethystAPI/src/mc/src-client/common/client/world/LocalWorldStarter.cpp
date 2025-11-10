#include "LocalWorldStarter.hpp"
#include <amethyst/Memory.hpp>

uint64_t World::LocalWorldStarter::startLocalWorld(const World::WorldID& worldId)
{
    using function = decltype(&LocalWorldStarter::startLocalWorld);
    static auto func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 56 48 83 EC ? 80 79 ? ? 48 8B F2"));
    return (this->*func)(worldId);
}
