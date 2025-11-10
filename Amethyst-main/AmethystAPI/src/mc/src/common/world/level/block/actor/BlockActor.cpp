#include "mc/src/common/world/level/block/actor/BlockActor.hpp"
#include <amethyst/Memory.hpp>

void BlockActor::moveTo(const BlockPos& pos)
{
    mPosition = pos;
}
