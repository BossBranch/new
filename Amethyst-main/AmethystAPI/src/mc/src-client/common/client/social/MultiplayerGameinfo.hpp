#pragma once
#include <cstddef>
#include <mc/src-deps/core/file/Path.hpp>
#include <string>
#include <vector>
#include <mc/src-client/common/client/social/GameConnectionInfo.hpp>

namespace Social {
enum class GamePublishSetting : int32_t {
    NoMultiPlay = 0x0000,
    InviteOnly = 0x0001,
    FriendsOnly = 0x0002,
    FriendsOfFriends = 0x0003,
    Public = 0x0004,
};

enum class MultiplayerServiceIdentifier : int32_t {
    XboxLive = 0x0000,
    Nintendo = 0x0001,
    AdHoc = 0x0002,
    Playstation = 0x0003,
    EDU = 0x0004,
    Mock = 0x0005,
    Invalid = 0xff,
};

class MultiplayerGameinfo {
public:
    std::byte padding1[16];
    std::vector<Social::GameConnectionInfo> mSupportedConnections;
    std::string mOwnerId;
    std::vector<uint64_t> mPlayerIds;
    std::string mOwnerNickname;
    std::string mHandleId;
    std::string mLevelId;
    std::string mSessionId;
    std::string mRakNetGUID;
    std::string mWorldName;
    std::string mWorldType;
    std::string mVersion;
    uint64_t mRealmId;
    std::string mThirdPartyServerId;
    std::string mThirdPartyServerIp;
    int32_t mThirdPartyServerPort;
    std::byte padding2[8];
    int64_t mGatheringId;
    std::byte padding3[8];
    std::byte padding4[32];
    std::string mOwnerPlayFabId;
    std::string mWorldName_1;
    int16_t mProtocol;
    int16_t mMaxMemberCount;
    int16_t mMemberCount;
    MultiplayerServiceIdentifier mServiceProvider;
    Core::Path mServiceIconPath;
    GamePublishSetting mBroadcastSetting;
    bool mLanGame;
    bool mOnlineCrossPlatformGame;
    std::byte padding5[2];
    int32_t mTransportLayer;
    std::byte padding6[4];
    int64_t mWebRTCNetworkId;
    int32_t mTitleId;
    bool mCrossPlayDisabled;
    bool mIsEditorWorld;
};
} // namespace Social