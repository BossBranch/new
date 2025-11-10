/// @symbols
#pragma once
#include <mc/src-deps/core/threading/Mutex.hpp>
#include <mc/src/common/world/level/ChunkBlockPos.hpp>
#include <mc/src/common/world/level/ChunkPos.hpp>
#include <mc/src/common/world/level/chunk/BlockVolume.hpp>
#include <mc/src/common/world/level/chunk/ChunkState.hpp>
#include <mc/src/common/world/level/chunk/LevelChunkFormat.hpp>
#include <mc/src/common/world/level/chunk/SubChunk.hpp>
#include <unordered_map>
#include <mc/src-deps/core/threading/SpinLock.hpp>
#include <mc/src/common/world/level/Tick.hpp>

class Block;
class BlockPos;
class BlockActor;
class BlockSource;
class Level;
class Dimension;
class ChunkSource;
class ActorLink;
class BlockTickingQueue;

enum class ChunkTerrainDataState : unsigned char {
    NoData = 0x0000,
    NeedsFixup = 0x0001,
    ReadyForGeneration = 0x0002,
    Generated = 0x0003,
    PostProcessed = 0x0004,
    Ready = 0x0005,
};

class LevelChunk {
public:
    /* this + 0    */ Bedrock::Threading::Mutex mBlockEntityAccessLock;
    /* this + 80   */ Level* mLevel;
    /* this + 88   */ Dimension* mDimension;
    /* this + 96   */ BlockPos mMin;
    /* this + 108  */ BlockPos mMax;
    /* this + 120  */ ChunkPos mPosition;
    /* this + 128  */ std::byte padding8[8];
    /* this + 136  */ ChunkSource* mGenerator;
    /* this + 144  */ std::optional<LevelChunkFormat> mLoadedFormat;    
    /* this + 152  */ std::string mSerializedEntitiesBuffer;
    /* this + 184  */ bool mHadSerializedEntities;
    /* this + 192  */ std::vector<ActorLink> mUnresolvedActorLinks;
    /* this + 216  */ std::atomic<ChunkState> mLoadState;
    /* this + 217  */ ChunkTerrainDataState mTerrainDataState;
    /* this + 224  */ SpinLock mCachedDataStateSpinLock;
    /* this + 256  */ SpinLock mClientRequestHeightmapAdjustSpinLock;
    /* this + 288  */ Tick mLastTick;
    /* this + 296  */ std::unique_ptr<BlockTickingQueue> mTickQueue;
    /* this + 304  */ std::unique_ptr<BlockTickingQueue> mRandomTickQueue;
    /* this + 312  */ std::vector<SubChunk> mSubChunks;
    /* this + 336  */ std::byte padding336[1348 - 336];
    /* this + 1348 */ std::array<ChunkLocalHeight, 256> mHeightmap;
    /* this + 1860 */ std::byte padding1860[4184 - 1860];
    /* this + 4184 */ std::unordered_map<ChunkBlockPos, std::shared_ptr<BlockActor>> mBlockEntities;

public:
    BlockActor* getBlockEntity(const ChunkBlockPos& chunkPos);

    // 1.21.0.3 - 40 ? 57 41 ? 48 83 ? ? 4C 8B ? 41 8B ? 48 8B ? 48 8B
    void setBlockVolume(const BlockVolume& blockVolume, uint32_t yOffset);
			  
    /// @sig {40 55 53 56 57 41 54 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 49 8B F1 4D 8B F8 48 8B DA}
    MC std::shared_ptr<BlockActor> _createBlockEntity(const BlockPos& pos, BlockSource* currentSource, const Block& current, const Block& old);

	/// @sig {48 89 5C 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8B FA 48 8B D9 48 89 54 24 ? 48 81 C1 ? ? ? ? 48 8B 43}
	MC void _placeBlockEntity(std::shared_ptr<BlockActor>);

    // 1.21.0.3 - 48 83 EC ? 4C 8B 89 ? ? ? ? 4C 8B DA 44 0F B7 52 ? 41 0F B7 C2 66 C1 F8 ? 4C 0F BF C0 48 8B 81 ? ? ? ? 48 B9 ? ? ? ? ? ? ? ? 49 2B C1 48 C1 F8 ? 48 0F AF C1 4C 3B C0 73 ? 4B 8D 04 40 48 C1 E0 ? 4A 8B 4C 08 ? 48 85 C9 74 ? 0F B6 12 66 41 83 E2 ? 45 0F B6 43 ? 48 8B 01 66 C1 E2 ? 66 41 03 D0 66 C1 E2 ? 48 8B 40 ? 66 41 03 D2 48 83 C4 ? 48 FF 25 ? ? ? ? E8 ? ? ? ? 48 8B 00 48 8B 80 ? ? ? ? 48 83 C4 ? C3 CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24
    const Block& getBlock(const ChunkBlockPos& pos) const;

    // Custom helper functions
    std::shared_ptr<BlockActor> getAndRemoveBlockActor(const ChunkBlockPos& pos);
    void setBlockActor(const ChunkBlockPos& pos, std::shared_ptr<BlockActor> actorShared);

    /// @sig {4C 8B 49 ? 44 0F BF D2}
    MC SubChunk* getSubChunk(short absoluteIndex);

    /// @signature {48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 80 B9 ? ? ? ? ? 49 8B F0 0F BF FA}
    MC bool _deserializeSubChunk(short subChunkIndex, class StringByteInput& stream);
};

static_assert(offsetof(LevelChunk, mBlockEntities) == 4184);