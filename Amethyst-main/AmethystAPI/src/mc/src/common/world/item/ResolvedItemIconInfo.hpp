#pragma once
#include <string>

enum ItemIconInfoType : __int32 {
    Icon = 0x0,
    Atlas = 0x1,
    RawUVs = 0x2,
    LegacyBlock = 0x3,
};

struct ResolvedItemIconInfo {
  std::string mIconName;
  int mIconFrame;
  ItemIconInfoType mIconType;
  unsigned int mRuntimeBlockID;
  float mU0;
  float mV0;
  float mU1;
  float mV1;
  unsigned __int16 mTexSizeW;
  unsigned __int16 mTexSizeH;

  ResolvedItemIconInfo(const std::string& icon, int frame, ItemIconInfoType type)
	  : mIconName(icon), mIconFrame(frame), mIconType(type),
		mRuntimeBlockID(0), mU0(0.0f), mV0(0.0f), mU1(0.0f), mV1(0.0f),
		mTexSizeW(0), mTexSizeH(0) {}
};