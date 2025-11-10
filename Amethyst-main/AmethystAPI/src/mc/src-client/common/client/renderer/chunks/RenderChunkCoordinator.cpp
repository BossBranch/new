#include "mc/src-client/common/client/renderer/chunks/RenderChunkCoordinator.hpp"
#include <amethyst/Memory.hpp>

void RenderChunkCoordinator::_setDirty(const BlockPos& from, const BlockPos& to, bool immediate, bool changesVisibility, bool canInterlock)
{
    using function = decltype(&RenderChunkCoordinator::_setDirty);
    static function func = std::bit_cast<function>(SigScan("48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 45 8B 28"));
    return (this->*func)(from, to, immediate, changesVisibility, canInterlock);
}