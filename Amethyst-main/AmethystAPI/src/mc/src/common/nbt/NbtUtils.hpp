#pragma once
#include "CompoundTagVariant.hpp"
#include "CompoundTag.hpp"
class BlockPos;

// helper file - not in game

class NbtUtils {
public:
	static CompoundTag writeBlockPos(const BlockPos& pos);
	static BlockPos readBlockPos(const CompoundTag& tag);
};