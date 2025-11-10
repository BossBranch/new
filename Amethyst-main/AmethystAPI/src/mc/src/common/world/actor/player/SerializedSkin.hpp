#pragma once
#include <string>
#include <vector>
#include <array>
#include <unordered_map>
#include <mc/src-deps/core/semVer/SemVersion.hpp>
#include <json/json.h>
#include <mc/src-deps/core/math/Color.hpp>
#include <mc/src-deps/core/image/Image.hpp>
#include <mc/src/common/world/actor/player/AnimatedImageData.hpp>
#include <mc/src-deps/core/utility/UUID.hpp>

namespace persona {
    enum class PieceType : uint32_t {
        Unknown = 0x0000,
        Skeleton = 0x0001,
        Body = 0x0002,
        Skin = 0x0003,
        Bottom = 0x0004,
        Feet = 0x0005,
        Dress = 0x0006,
        Top = 0x0007,
        High_Pants = 0x0008,
        Hands = 0x0009,
        Outerwear = 0x000a,
        FacialHair = 0x000b,
        Mouth = 0x000c,
        Eyes = 0x000d,
        Hair = 0x000e,
        Hood = 0x000f,
        Back = 0x0010,
        FaceAccessory = 0x0011,
        Head = 0x0012,
        Legs = 0x0013,
        LeftLeg = 0x0014,
        RightLeg = 0x0015,
        Arms = 0x0016,
        LeftArm = 0x0017,
        RightArm = 0x0018,
        Capes = 0x0019,
        ClassicSkin = 0x001a,
        Emote = 0x001b,
        Unsupported = 0x001c,
        Count = 0x001d,
        };
}

class SerializedPersonaPieceHandle {
public:
    std::string mPieceId;
    persona::PieceType mPieceType;
    mce::UUID mPackId;
    bool mIsDefaultPiece;
    std::string mProductId;
};

class TintMapColor { 
public: 
    std::array<mce::Color, 4> colors;
};

enum class TrustedSkinFlag : char {
  Unset = 0x0000,
  False = 0x0001,
  True = 0x0002,
};

class SerializedSkin {
public:
    std::string mId;
    std::string mPlayFabId;
    std::string mFullId;
    std::string mResourcePatch;
    std::string mDefaultGeometryName;
    mce::Image mSkinImage;
    mce::Image mCapeImage;
    std::vector<AnimatedImageData> mSkinAnimatedImages;
    Json::Value mGeometryData;
    SemVersion mGeometryDataEngineVersion;
    Json::Value mGeometryDataMutable;
    std::string mAnimationData;
    std::string mCapeId;
    std::vector<SerializedPersonaPieceHandle> mPersonaPieces;
    std::byte mArmSizeType[8];
    std::unordered_map<enum persona::PieceType, TintMapColor> mPieceTintColors;
    mce::Color mSkinColor;
    TrustedSkinFlag mIsTrustedSkin;
    bool mIsPremium;
    bool mIsPersona;
    bool mIsPersonaCapeOnClassicSkin;
    bool mIsPrimaryUser;
    bool mOverridesPlayerAppearance;
};