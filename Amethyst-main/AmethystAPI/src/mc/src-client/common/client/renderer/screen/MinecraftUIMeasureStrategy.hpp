#pragma once
#include <mc/src-client/common/client/gui/controls/UIMeasureStrategy.hpp>

class UIProfanityContext;

class MinecraftUIMeasureStrategy : public UIMeasureStrategy {
public:
    const UIProfanityContext& mUIProfanityContext;
};