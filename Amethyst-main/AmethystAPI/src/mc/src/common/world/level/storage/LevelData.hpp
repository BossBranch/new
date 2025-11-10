#pragma once
#include "mc/src-deps/core/semVer/SemVersion.hpp"
#include "mc/src-deps/core/string/StringHash.hpp"
#include "mc/src/common/world/level/LevelSettings.hpp"
#include "json/json.h"
#include "mc/src/common/world/level/storage/StorageVersion.hpp"
#include "mc/src/common/world/level/storage/ExperimentsStorage.hpp"
#include <mc/src/common/resources/BaseGameVersion.hpp>
#include "mc/src/common/world/level/Tick.hpp"
#include <mc/src/common/world/actor/player/Abilities.hpp>
#include <mc/src/common/GameVersion.hpp>
#include <variant>
#include <mc/src/common/nbt/CompoundTag.hpp>
#include <mc/src-deps/core/resource/ContentIdentity.hpp>

struct LevelDataValue {
public:
    class Tag {
    public:
        std::unique_ptr<CompoundTag> mTag;
    };

    std::variant<int, bool, float, std::string, enum GeneratorType, enum GameType, BlockPos, LevelSeed64, LevelDataValue::Tag, enum DaylightCycle> mValue;
};

struct AdventureSettings
{
    bool noPvM;
    bool noMvP;
    bool immutableWorld;
    bool showNameTags;
    bool autoJump;
};

struct WorldTemplateLevelData {
    ContentIdentity mPremiumTemplateContentIdentity;
    PackIdVersion mWorldTemplateIdentity;
    BaseGameVersion mBaseGameVersion;
    BaseGameVersion mMaxBaseGameVersion;
    bool mIsFromWorldTemplate;
    bool mIsWorldTemplateOptionLocked;
};

class LevelData {
public:
    AdventureSettings mAdventureSettings;
    WorldTemplateLevelData mWorldTemplateLevelData; // 8
    GameRules mGameRules; // 416
    ExperimentsStorage mExperiments; // 608
    Abilities mDefaultAbilities;
    PermissionsHandler mDefaultPermissions;
    std::string mLevelName;
    StorageVersion mStorageVersion;
    GameVersion mMinCompatibleClientVersion;
    int mNetworkVersion;
    SemVersion mInventoryVersion;
    Tick mCurrentTick; // should be at 1128
    bool mDontTickBlocksForTest;
    bool mRedstoneTickingEnabled;
    bool mHasSpawnPos;
    BlockPos mLimitedWorldOrigin;
    int mTime;
    int64_t mLastSaved;
    unsigned int mServerTickRange;
    float mRainLevel; // 1172
    int mRainTime;
    float mLightningLevel;
    int mLightningTime;
    int mNetherScale;
    GameVersion mLastOpenedWithVersion;
    Difficulty mGameDifficulty;
    bool mForceGameType;
    bool mIsHardcore;
    bool mSpawnMobs;
    bool mAdventureModeOverridesEnabled;
    Json::Value mFlatworldGeneratorOptions;
    unsigned int mWorldStartCount;
    bool mAchievementsDisabled;
    Editor::WorldType mEditorWorldType;
    bool mIsCreatedInEditor;
    bool mIsExportedFromEditor;
    alignas(8) EducationEditionOfferValue mEducationEditionOffer; // 1288
    std::optional<CloudSaveLevelInfo> mCloudSaveInfo; // 1296
    bool mEducationFeaturesEnabled; // 1440
    bool mIsSingleUseWorld; // 1441
    bool mConfirmedPlatformLockedContent;
    bool mMultiplayerGameIntent;
    bool mMultiplayerGame;
    bool mLANBroadcastIntent;
    bool mLANBroadcast; // 1446
    Social::GamePublishSetting mXBLBroadcastIntent;
    Social::GamePublishSetting mXBLBroadcastMode;
    Social::GamePublishSetting mPlatformBroadcastIntent;
    Social::GamePublishSetting mPlatformBroadcastMode;
    bool mCheatsEnabled;
    bool mCommandsEnabled;
    bool mTexturePacksRequired;
    bool mHasLockedBehaviorPack;
    bool mHasLockedResourcePack;
    bool mIsFromLockedTemplate;
    bool mIsRandomSeedAllowed;
    std::string mEducationProductId;
    bool mUseMsaGamertagsOnly;
    bool mBonusChestEnabled;
    bool mBonusChestSpawned;
    bool mStartWithMapEnabled;
    bool mMapsCenteredToOrigin;
    bool mRequiresCopiedPackRemovalCheck;
    bool mSpawnV1Villagers;
    bool mPersonaDisabled;
    bool mCustomSkinsDisabled;
    bool mEmoteChatMuted;
    NetherWorldType mNetherType; // 1514
    SpawnSettings mSpawnSettings;
    std::unordered_map<HashedString, LevelDataValue> mValues;
    std::unordered_map<HashedString, LevelDataValue> mOverrides;
    std::string mBiomeOverride;
    std::optional<GeneratorType> mDataDrivenGeneratorType;
    ChatRestrictionLevel mChatRestrictionLevel; // 1736
    std::unique_ptr<Bedrock::PubSub::Publisher<void __cdecl(bool),Bedrock::PubSub::ThreadModel::SingleThreaded>> mIsHardcoreSubscribers;

public:
    static LevelData $ctor(bool useEducationEditionFeatures);

    GameType getGameType() const;
    LevelSeed64 getSeed() const;
    const std::string& getEducationOid() const;
};

static_assert(offsetof(LevelData, mLevelName) == 912);