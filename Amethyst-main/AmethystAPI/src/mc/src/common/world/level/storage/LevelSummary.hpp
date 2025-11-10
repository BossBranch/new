#pragma once
#include <string>
#include <mc/src/common/world/level/storage/StorageVersion.hpp>
#include <mc/src/common/world/level/storage/LevelData.hpp>
#include <mc/src/common/world/level/storage/Experiments.hpp>
#include <mc/src/common/GameVersion.hpp>
#include <mc/src-deps/core/resource/ContentIdentity.hpp>

namespace EduCloud {

enum class WorldSyncState : int {
	None        = 0,
	Synced      = 1,
	Warning     = 2,
	Critical    = 3,
	Placeholder = 4,
	Off         = 5,
};

}

class LevelSummary {
public:
	std::string mId;
	std::string mName;
	int64_t mLastSaved;
	GameType mGameType;
	bool mIsHardcore;
	Difficulty mGameDifficulty;
	LevelSeed64 mSeed;
	int mNetworkProtocolVersion;
	uint64_t mSizeOnDisk;
	bool mConfirmedPlatformLockedContent;
	bool mIsMultiplayerEnabled;
	bool mLANBroadcastIntent;
	Social::GamePublishSetting mXBLBroadcastIntent;
	bool mCommandsEnabled;
	EducationEditionOfferValue mEducationEditionOffer;
	GameVersion mLastLoadedGameVersion;
	GameVersion mMinCompatibleClientVersion;
	StorageVersion mStorageVersion;
	Core::PathBuffer<std::string> mWorldIconPath;
	Core::PathBuffer<std::string> mWorldIconTargetPath;
	ContentIdentity mPremiumTemplateContentIdentity;
	std::string mEducationOid;
	Experiments mExperiments;
	BaseGameVersion mBaseGameVersion;
	bool mIsSingleUseWorld;
	bool mIsBetaRetailLevel;
	EduSharedUriResource mEduSharedUriResource;
	Editor::WorldType mEditorWorldType;
	std::optional<CloudSaveLevelInfo> mCloudSaveInfo;
	EduCloud::WorldSyncState mEduCloudWorldSyncState;

	//LevelSummary(const std::string& id, const LevelData& levelData, const Core::Path& a4, const Core::Path& a5, bool a6);

	static LevelSummary $ctor(const std::string& id, const LevelData& levelData, const Core::Path& a4, const Core::Path& a5, bool a6);
};