#pragma once
#include <memory>
#include <mc/src-deps/core/utility/NonOwnerPointer.hpp>
#include <mc/src-deps/core/threading/EnableQueueForMainThread.hpp>
#include <mc/src-deps/core/string/StringHash.hpp>
#include <string>
#include <vector>
#include <json/json.h>
#include <glm/vec2.hpp>

enum class ToastMessageType : int32_t {
    Unknown = 0x0000,
    Achievement = 0x0001,
    Invite = 0x0002,
    RawInvite = 0x0003,
    FocusLost = 0x0004,
    ImportResourcePack = 0x0005,
    ImportExportWorld = 0x0006,
    GlobalResourceCrashRecovery = 0x0007,
    Message = 0x0008,
    StorePromotion = 0x0009,
    ServerPromotion = 0x000a,
    BrazeExternalLink = 0x000b,
    DialogMessage = 0x000c,
};

class IToastListener;

struct ToastIconData {
    int iconId;
    HashedString iconTag;
};

class ToastMessage {
public:
    IToastListener *mListener;
    bool mIsMergingEnabled;
    bool mHasCustomPocketToast;
    bool mUseCustomPocketToast;
    ToastMessageType mType;
    std::string mTitle;
    std::string mSubtitle;
    std::string mAction;
    std::string mMessageId;
    std::string mButtonId;
    Json::Value mPropertyBag;
    std::string mLink;
    bool mHasBeenPressed;
    float mTransitInTime;
    float mTransitOutTime;
    float mAdditionalDisplaySeconds;
    float mAlpha;
    float mBackgroundAlpha;
    glm::vec2 mStartPosition;
    glm::vec2 mIdlePosition;
    glm::vec2 mEndPosition;
    glm::vec2 mCustomPocketStartPosition;
    glm::vec2 mCustomPocketIdlePosition;
    glm::vec2 mCustomPocketEndPosition;
    std::vector<ToastIconData> mIconRenderIds;
    std::string mControlId;
    std::string mPocketControlId;

    ToastMessage(ToastMessageType messageType, const std::string& mTitle, const std::string& mSubtitle, const Json::Value& propertyBag, float mAdditionalDisplaySeconds) 
        : mType(messageType), mTitle(mTitle), mSubtitle(mSubtitle), mPropertyBag(propertyBag), mAdditionalDisplaySeconds(mAdditionalDisplaySeconds),
          mListener(nullptr), mIsMergingEnabled(true), mHasCustomPocketToast(false), mUseCustomPocketToast(false), mAction(""), mMessageId(""), mButtonId(""),
          mLink(""), mHasBeenPressed(false), mTransitInTime(0.5f), mTransitOutTime(0.5f), mAlpha(1.0f), mBackgroundAlpha(0.8f),
          mStartPosition(0.0f, 0.0f), mIdlePosition(0.0f, 0.0f), mEndPosition(0.0f, 0.0f),
          mCustomPocketStartPosition(0.0f, 0.0f), mCustomPocketIdlePosition(0.0f, 0.0f), mCustomPocketEndPosition(0.0f, 0.0f),
          mControlId(""), mPocketControlId("") {}

    ToastMessage(ToastMessageType messageType, const std::string& title, const std::string& subtitle) 
        : ToastMessage(messageType, title, subtitle, Json::Value::null, 0.0f) {}
};

class ToastManager : Bedrock::Threading::EnableQueueForMainThread, Bedrock::EnableNonOwnerReferences, std::enable_shared_from_this<ToastManager> {
public:
    virtual ~ToastManager() = default;
    virtual void pushToast(ToastMessage&& toast);
};