#pragma once
#include <amethyst/game/CreativeItemRegistry.hpp>

class Minecraft;

namespace Amethyst {
class SharedContext {
public:
    // Amethyst APIs
    Amethyst::CreativeItemRegistry mCreativeRegistry;

    // Minecraft Specifics
    Minecraft* mMinecraft = nullptr;

protected:
    SharedContext();
};
}