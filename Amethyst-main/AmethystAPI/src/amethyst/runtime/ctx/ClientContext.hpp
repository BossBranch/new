#pragma once
#include "amethyst/runtime/ctx/SharedContext.hpp"

class ClientInstance;
class MinecraftInputHandler;
class Options;

namespace Amethyst {

class ClientContext : public Amethyst::SharedContext {
public:
    ClientInstance* mClientInstance = nullptr;
    MinecraftInputHandler* mMcInputHandler = nullptr;
    Options* mOptions = nullptr;
    bool mIsInWorldOrLoading = false;
};

}