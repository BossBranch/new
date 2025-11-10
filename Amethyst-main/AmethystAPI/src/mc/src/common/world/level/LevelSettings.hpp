#pragma once
#include <string>
#include <mc/src/common/world/level/GameType.hpp>
#include <mc/src/common/util/NewType.hpp>
#include <mc/src-deps/core/utility/AutomaticID.hpp>
#include <vector>
#include <optional>
#include <mc/src/common/world/level/BlockPos.hpp>
#include <mc/src-deps/core/resource/ResourceHelper.hpp>
#include <mc/src/common/world/level/storage/GameRules.hpp>
#include <mc/src/common/world/level/storage/ExperimentsStorage.hpp>
#include <mc/src/common/resources/BaseGameVersion.hpp>
#include <mc/src/common/world/Difficulty.hpp>
#include <mc/src-client/common/client/social/MultiplayerGameinfo.hpp>
#include <mc/src/common/world/actor/player/Abilities.hpp>

class LevelData;

enum class GeneratorType : int {
    Legacy    = 0,
    Overworld = 1,
    Flat      = 2,
    Nether    = 3,
    TheEnd    = 4,
    Void      = 5,
    Undefined = 6,
};

class EducationEditionOfferValue {
    std::byte padding0[4];
};

enum class WorldVersion : uint8_t {
    Pre1_18  = 0,
    Post1_18 = 1,
};

enum class SpawnBiomeType : short {
    Default     = 0,
    UserDefined = 1,
};

struct SpawnSettings
{
    SpawnBiomeType type;
    std::string userDefinedBiomeName;
    DimensionType dimension;
};

class LevelSeed64 {
public:
    uint64_t mValue;

    LevelSeed64() : mValue(0) {}
    LevelSeed64(uint64_t seed) : mValue(seed) {}
};

namespace Editor {
enum class WorldType : int {
    NonEditor          = 0,
    EditorProject      = 1,
    EditorTestLevel    = 2,
    EditorRealmsUpload = 3,
};
}

enum class NetherWorldType : uint8_t {
    Normal = 0,
    Flat   = 1,
};

enum class DaylightCycle : uint8_t {
    Normal    = 0,
    AlwaysDay = 1,
    LockTime  = 2,
};

struct PackInstanceId {
    PackIdVersion mPackId;
    std::string mSubpackName;
};

struct EduSharedUriResource {
    std::string linkUri;
    std::string buttonName;
};

enum class ForceBlockNetworkIdsAreHashes : uint8_t {
    UseDefault = 0,
    ForceOff   = 1,
    ForceOn    = 2,
};

enum class ChatRestrictionLevel : uint8_t {
    None     = 0,
    Dropped  = 1,
    Disabled = 2,
};

class CloudSaveLevelInfo {
    std::string mDriveItemId;
    std::string mCTag;
    std::string mUserId;
    std::string mFileName;
    bool mNeedsUpload;
    int mVersionId;
};

class EducationLocalLevelSettings {
    std::optional<std::string> codeBuilderOverrideUri;
};

class AgentCapabilities {
    std::optional<bool> canModifyBlocks;
};

class ExternalLinkSettings {
    std::string url;
    std::string displayName;
};

class EducationLevelSettings
{
    std::string codeBuilderDefaultUri;
    std::string codeBuilderTitle;
    bool canResizeCodeBuilder;
    bool disableLegacyTitleBar;
    std::string postProcessFilter;
    std::string screenshotBorderResourcePath;
    std::unordered_map<std::string, unsigned int> hiddenCommands;
    EducationLocalLevelSettings localSettings;
    std::optional<AgentCapabilities> agentCapabilities;
    std::optional<ExternalLinkSettings> externalLinkSettings;
};

class LevelSettings {
public:
    LevelSeed64 mSeed;
    GameType mGameType;
    bool mIsHardcore;
    Difficulty mGameDifficulty;
    bool mForceGameType;
    GeneratorType mGenerator;
    WorldVersion mWorldVersion;
    NetherWorldType mNetherType; // 29
    SpawnSettings mSpawnSettings;
    bool mAchievementsDisabled;
    Editor::WorldType mEditorWorldType;
    bool mIsCreatedInEditor;
    bool mIsExportedFromEditor;
    int mTime;
    EducationEditionOfferValue mEducationEditionOffer;
    bool mEducationFeaturesEnabled;
    bool mImmutableWorld;
    float mRainLevel;
    float mLightningLevel;
    bool mConfirmedPlatformLockedContent;
    bool mMultiplayerGameIntent;
    bool mLANBroadcastIntent;
    Social::GamePublishSetting mXBLBroadcastIntent;
    Social::GamePublishSetting mPlatformBroadcastIntent;
    DaylightCycle mDaylightCycle;
    bool mDisablePlayerInteractions;
    bool mCheatsEnabled;
    bool mAdventureModeOverridesEnabled;
    bool mCommandsEnabled;
    bool mTexturePacksRequired;
    bool mHasLockedBehaviorPack;
    bool mHasLockedResourcePack;
    bool mIsFromLockedTemplate;
    bool mIsRandomSeedAllowed;
    bool mUseMsaGamertagsOnly;
    bool mOverrideSettings;
    bool mBonusChestEnabled;
    bool mStartWithMapEnabled;
    int mServerChunkTickRange;
    bool mIsFromWorldTemplate;
    bool mIsWorldTemplateOptionLocked;
    bool mSpawnV1Villagers; // 146
    bool mPersonaDisabled;
    bool mCustomSkinsDisabled;
    bool mEmoteChatMuted;
    int mLimitedWorldWidth;
    int mLimitedWorldDepth;
    PermissionsHandler mDefaultPermissions;
    BlockPos mDefaultSpawn; // 164
    std::vector<PackInstanceId> mNewWorldBehaviorPackIdentities;
    std::vector<PackInstanceId> mNewWorldResourcePackIdentities;
    GameRules mGameRules;
    ExperimentsStorage mExperiments;
    BaseGameVersion mBaseGameVersion;
    std::string mEducationProductID;
    std::string mBiomeOverride;
    EduSharedUriResource mEduSharedUriResource;
    ChatRestrictionLevel mChatRestrictionLevel;
    std::string mServerId; // 744
    std::string mWorldId;
    std::string mScenarioId; // 808
    alignas(8) std::optional<EducationLevelSettings> mEducationLevelSettings; // 840
    alignas(8) std::optional<bool> mOverrideForceExperimentalGameplayFlag;  
    alignas(8) std::optional<CloudSaveLevelInfo> mCloudSaveInfo;             
    std::vector<std::string> mExcludedScriptModules; // 1320
    //bool mAddExperiments; // 1328
    //bool mOverrideBaseGameVersion;
    //ForceBlockNetworkIdsAreHashes mForceBlockNetworkIdsAreHashes;

public:
    static LevelSettings $ctor(const LevelData& levelData, DimensionType dimType);
    static LevelSettings* $ctorPtr(const LevelData& levelData, DimensionType dimType);
};

//static_assert(sizeof(LevelSettings) == 1344);