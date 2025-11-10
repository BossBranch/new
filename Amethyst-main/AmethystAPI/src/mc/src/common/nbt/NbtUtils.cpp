#include "NbtUtils.hpp"
#include <mc/src/common/world/level/BlockPos.hpp>

CompoundTag NbtUtils::writeBlockPos(const BlockPos& pos) {
    CompoundTag tag;
	tag.putInt("x", pos.x);
	tag.putInt("y", pos.y);
	tag.putInt("z", pos.z);
    return tag;
}

BlockPos NbtUtils::readBlockPos(const CompoundTag& tag) {
    int x = tag.getInt("x");
    int y = tag.getInt("y");
    int z = tag.getInt("z");
    return BlockPos(x, y, z);
}
