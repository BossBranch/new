#pragma once
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <mc/src/common/world/level/ChunkPos.hpp>

class SpinLock;
class IDataOutput;
class IDataInput;
class BlockPalette;
class SubChunkPos;
struct DeserializationChanges;

struct DirtyTicksCounter {
    int totalTime;
    int lastChange;
};

class SubChunkBrightnessStorage;


template <typename T>
class SubChunkStorage {
    virtual ~SubChunkStorage() = default;
};

class Block;

// align 2 means that mNeedsInitLighting shares the same 8 bytes as mHasMaxSkyLight
// prevents mBlocks getting misaligned by 8
#pragma pack(push, 2) 
struct SubChunk {
public:
    enum class SubChunkState : int32_t {};

    DirtyTicksCounter mDirtyTicksCounter;
    std::unique_ptr<SubChunkBrightnessStorage> mSkyLight;
    std::unique_ptr<SubChunkBrightnessStorage> mBlockLight;
    bool mHasMaxSkyLight;
    SubChunk::SubChunkState mSubChunkState;
    bool mNeedsInitLighting;
    bool mNeedsClientLighting;
    std::unique_ptr<SubChunkStorage<Block>> mBlocks[2]; // layers, 0 = base, 1 = water(?) probably
    SubChunkStorage<Block>* mBlocksReadPtr[2];
    SpinLock* mWriteLock;
    unsigned __int64 mHash;
    bool mHashDirty;
    char mAbsoluteIndex;
    bool mIsReplacementSubChunk;
    uint8_t mRenderChunkTrackingVersionNumber;

public:
    // @signature {48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 54 41 56 41 57 48 81 EC ? ? ? ? 41 0F B6 E8}
    void serialize(IDataOutput& steam, bool network) const;

    // @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 4C 89 4C 24 ? 49 8B F8 48 8B DA}
    void deserialize(IDataInput& steam, const BlockPalette& pallette, const SubChunkPos& pos, std::optional<DeserializationChanges*> changes);

public:
    virtual ~SubChunk() = default;
};
#pragma pack(pop)

static_assert(offsetof(SubChunk, mWriteLock) == 72);