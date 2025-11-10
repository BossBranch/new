#pragma once
#include <functional>
#include <mc/src/common/world/level/BlockPos.hpp>
#include <mc/src/common/world/level/ChunkPos.hpp>

struct SubChunkPos {
    int x;
    int y;
    int z;

    SubChunkPos(int x, int y, int z) : x(x), y(y), z(z) {}
    SubChunkPos(const SubChunkPos& other) : x(other.x), y(other.y), z(other.z) {}
    SubChunkPos(const SubChunkPos&& other) noexcept : x(other.x), y(other.y), z(other.z) {}

    SubChunkPos(const BlockPos& pos) : x(pos.x / 16), y(pos.y / 16), z(pos.z / 16) {}
    SubChunkPos(const ChunkPos& pos, int subChunkY) : x(pos.x), y(subChunkY), z(pos.z) {}

    constexpr size_t hashCode() const
    {
        // This implementation is completely guessed, please verify it for usage in actual game memory
        // only needed right now for mod memory, so impl hasn't been checked.
        size_t hash = 0;
        mce::Math::hash_accumulate(hash, x);
        mce::Math::hash_accumulate(hash, y);
        mce::Math::hash_accumulate(hash, z);
        return hash;
    }

    bool operator==(const SubChunkPos& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }
};

// regular hash specialization causes errors:
// idfk why - so just define our own hasher
// 
//2 > C :\Users\blake\Documents\Modding\Amethyst\AmethystAPI\src\minecraft\src\common\world\level\SubChunkPos.hpp(37) : error C2908 : explicit specialization;
//'std::hash<SubChunkPos>' has already been instantiated 2 > C :\Users\blake\Documents\Modding\Amethyst\AmethystAPI\src\minecraft\src\common\world\level\SubChunkPos.hpp(37) : error C2766 : explicit specialization;

struct SubChunkPosHasher {
    size_t operator()(const SubChunkPos& pos) const
    {
        return pos.hashCode();
    }
};