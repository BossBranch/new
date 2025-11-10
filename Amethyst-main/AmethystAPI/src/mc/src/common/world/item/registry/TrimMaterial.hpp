#pragma once
#include "mc/src-deps/core/string/StringHash.hpp"

class TrimMaterial {
public:
    HashedString mMaterialId;
    std::string mColor;
    HashedString mItemName;
};