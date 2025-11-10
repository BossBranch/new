#pragma once
#include "mc/src-deps/core/math/Color.hpp"
#include "mc/src/common/world/level/block/components/BlockComponentBase.hpp"

struct BlockMapColorComponent : public BlockComponentBase {
public:
    mce::Color mMapColor;
};