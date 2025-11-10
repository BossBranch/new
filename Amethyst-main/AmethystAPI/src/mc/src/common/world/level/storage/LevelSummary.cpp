#include "LevelSummary.hpp"

//LevelSummary::LevelSummary(const std::string& id, const LevelData& levelData, const Core::Path& a4, const Core::Path& a5, bool a6)
//{
//    mId = id;
//    mName = levelData.mLevelName;
//    mLastSaved = levelData.mLastSaved;
//
//    mGameType = levelData.getGameType();
//    mIsHardcore = levelData.mIsHardcore;
//    mGameDifficulty = levelData.mGameDifficulty;
//    mSeed = levelData.getSeed();
//
//    mNetworkProtocolVersion = levelData.mNetworkVersion;
//    mConfirmedPlatformLockedContent = levelData.mConfirmedPlatformLockedContent;
//    mIsMultiplayerEnabled = levelData.mMultiplayerGameIntent;
//    mLANBroadcastIntent = levelData.mLANBroadcastIntent;
//    mXBLBroadcastIntent = levelData.mXBLBroadcastIntent;
//    mCommandsEnabled = levelData.mCommandsEnabled;
//    mEducationEditionOffer = levelData.mEducationEditionOffer;
//
//    mLastLoadedGameVersion = levelData.mLastOpenedWithVersion;
//    mMinCompatibleClientVersion = levelData.mMinCompatibleClientVersion;
//    mStorageVersion = levelData.mStorageVersion;
//
//    mWorldIconPath = Core::PathBuffer<std::string>();
//    mWorldIconTargetPath = Core::PathBuffer<std::string>();
//
//    mPremiumTemplateContentIdentity = levelData.mWorldTemplateLevelData.mPremiumTemplateContentIdentity;
//    mEducationOid = levelData.getEducationOid();
//
//    mExperiments = levelData.mExperiments;
//
//    mIsSingleUseWorld = levelData.mIsSingleUseWorld;
//    mIsBetaRetailLevel = a6;
//
//    mEduSharedUriResource.buttonName = "";
//    mEduSharedUriResource.linkUri = "";
//    mEditorWorldType = levelData.mEditorWorldType;
//
//    // TODO NEED TO CALL Core::FileSystem::getFileOrDirectorySize(v22, a4, self + 104);
//
//    // AND
//
//    // LevelSummary::_initializeWorldIconPath(self, v18);
//    mSizeOnDisk = 0;
//
//    mCloudSaveInfo = std::nullopt;
//    mEduCloudWorldSyncState = EduCloud::WorldSyncState::None;
//}

LevelSummary LevelSummary::$ctor(const std::string& id, const LevelData& levelData, const Core::Path& a4, const Core::Path& a5, bool a6) {
    alignas(LevelData) std::byte storage[sizeof(LevelSummary)];
    auto obj = reinterpret_cast<LevelSummary*>(&storage);

    using function = void(__fastcall*)(LevelSummary*, const std::string&, const LevelData&, const Core::Path&, const Core::Path&, bool);
    static auto func = std::bit_cast<function>(SigScan("40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 4C 89 4C 24 ? 49 8B D8 48 8B F9"));
    func(obj, id, levelData, a4, a5, a6);

    return std::move(*obj);
}