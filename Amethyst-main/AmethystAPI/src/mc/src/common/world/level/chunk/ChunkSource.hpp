#pragma once
#include <memory>
#include <atomic>
#include <unordered_map>

#include <mc/src-deps/core/utility/NonOwnerPointer.hpp>
#include <mc/src-deps/core/utility/pubsub/Subscription.hpp>

class Level;
class LevelChunk;
class LevelChunkBuilderData;
class LevelChunkMetaDataDictionary;
class ChunkPos;
class Dimension;
class Random;
class ChunkKey;
struct ActorUnloadedChunkTransferEntry;
class BlendingDataProvider;
class ChunkViewSource;

/**@vtable*/
class ChunkSource : public Bedrock::EnableNonOwnerReferences {
public:
    enum class LoadMode : int {
        None = 0x0,
        Deferred = 0x1,
    };

public:
    int mChunkSide;                             
    Level* mLevel;                        
    Dimension* mDimension;               
    ChunkSource* mParent;                           
    std::unique_ptr<ChunkSource> mOwnedParent;     
    LevelChunkBuilderData* mLevelChunkBuilderData; 
    std::atomic<bool> mShuttingDown;               
    Bedrock::PubSub::Subscription mOnSaveSubscription;
    Bedrock::PubSub::Subscription mOnLevelStorageAppSuspendSubscription;                     

public:
	/**
	* @symbol {??1ChunkSource@@UEAA@XZ}
	* @vidx {0} 
	*/
	virtual ~ChunkSource();
    
	/**@vidx {1} */
	virtual void shutdown();
    
	/**@vidx {2} */
	virtual bool isShutdownDone();
    
	/**@vidx {3} */
	virtual std::shared_ptr<LevelChunk> getExistingChunk(const ChunkPos&);
    
	/**@vidx {4} */
	virtual std::shared_ptr<LevelChunk> getRandomChunk(Random& random);
    
	/**@vidx {5} */
	virtual bool isChunkKnown(const ChunkPos& chunkPos);
    
	/**@vidx {6} */
	virtual bool isChunkSaved(const ChunkPos& chunkPos);
    
	/**@vidx {7} */
	virtual std::shared_ptr<LevelChunk> createNewChunk(const ChunkPos& cp, ChunkSource::LoadMode lm, bool readOnly);
    
	/**@vidx {8} */
	virtual std::shared_ptr<LevelChunk> getOrLoadChunk(const ChunkPos& cp, ChunkSource::LoadMode lm, bool readOnly);
    
	/**@vidx {9} */
	virtual bool postProcess(ChunkViewSource& neighborhood);
    
	/**@vidx {10} */
	virtual void checkAndReplaceChunk(ChunkViewSource& neighborhood, LevelChunk& lc);
    
	/**@vidx {11} */
	virtual void loadChunk(LevelChunk& lc, bool forceImmediateReplacementDataLoad);
    
	/**@vidx {12} */
	virtual void postProcessMobsAt(class BlockSource& region, int chunkWestBlock, int chunkNorthBlock, Random& random);
    
	/**@vidx {13} */
	virtual bool saveLiveChunk(LevelChunk& lc);
    
	/**@vidx {14} */
	virtual void writeEntityChunkTransfer(LevelChunk& levelChunk);
    
	/**@vidx {15} */
	virtual void writeEntityChunkTransfersToUnloadedChunk(const ChunkKey&, const std::vector<ActorUnloadedChunkTransferEntry>&);
    
	/**@vidx {16} */
	virtual void deserializeActorStorageToLevelChunk(LevelChunk&);
    
	/**@vidx {17} */
	virtual void hintDiscardBatchBegin();
    
	/**@vidx {18} */
	virtual void hintDiscardBatchEnd();
    
	/**@vidx {19} */
	virtual void acquireDiscarded(std::unique_ptr<LevelChunk, struct LevelChunkFinalDeleter> ptr);
    
	/**@vidx {20} */
	virtual void compact();
    
	/**@vidx {21} */
	virtual void flushPendingDiscardedChunkWrites();
    
	/**@vidx {22} */
	virtual void flushThreadBatch();
    
	/**@vidx {23} */
	virtual bool isWithinWorldLimit(const ChunkPos& cp) const;
    
	/**@vidx {24} */
	virtual const std::unordered_map<ChunkPos, std::weak_ptr<LevelChunk>>* getChunkMap();
    
	/**@vidx {25} */
	virtual const std::unordered_map<ChunkPos, std::weak_ptr<LevelChunk>>& getStorage() const;
    
	/**@vidx {26} */
	virtual void clearDeletedEntities();
    
	/**@vidx {27} */
	virtual bool canCreateViews() const;
    
	/**@vidx {28} */
	virtual std::unique_ptr<BlendingDataProvider> tryGetBlendingDataProvider();
    
	/**@vidx {29} */
	virtual std::shared_ptr<LevelChunkMetaDataDictionary> loadLevelChunkMetaDataDictionary();
    
	/**@vidx {30} */
	virtual void setLevelChunk(std::shared_ptr<LevelChunk>);
    
	/**@vidx {31} */
	virtual bool canLaunchTasks() const;
    
	/**@vidx {32} */
	virtual bool chunkPosNeedsBlending(const ChunkPos& cp);

public:
    ChunkSource(Dimension* dimension, int side);
};

static_assert(sizeof(ChunkSource) == 0x70, "ChunkSource size is incorrect");