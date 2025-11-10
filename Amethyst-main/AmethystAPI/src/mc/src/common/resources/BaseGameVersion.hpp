#pragma once
#include "mc/src-deps/core/semVer/SemVersion.hpp"

class BaseGameVersion {
public:
    SemVersion mSemVersion;
    bool mNeverCompatible;
};