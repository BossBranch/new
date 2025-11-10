#pragma once
#include <mc/src/common/world/level/LevelListener.hpp>
#include <bitset>
#include <unordered_map>
#include <mc/src/common/world/level/chunk/SubChunk.hpp>

class RenderChunkCoordinator : public LevelListener {
public:
    //struct DirtyChunkData {
    //public:
    //    bool mImmediate;
    //    bool mChangesVisibility;
    //    std::bitset<6> mInterlockBitField;
    //};

    //std::byte padding8[136 - 8];
    //std::unordered_map<SubChunkPos, RenderChunkCoordinator::DirtyChunkData, SubChunkPosHasher> mDirtyChunks;

    /// @signature {48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 45 8B 28}
    void _setDirty(const BlockPos& from, const BlockPos& to, bool immediate, bool changesVisibility, bool canInterlock);
};