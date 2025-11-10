/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>
#include "glm/glm.hpp"

class MinecraftUIRenderContext;
class IClientInstance;
struct RectangleArea;


class HoverRenderer {
public:
    uintptr_t** vtable;
    std::byte padding[48];
    std::string mFilteredContent; // this + 56
    glm::tvec2<float> mCursorPosition; // this + 88
    glm::tvec2<float> mOffset; // this + 96
    MC static uintptr_t $vtable_for_this;
/// @signature {48 8B C4 48 89 58 ? 48 89 70 ? 48 89 78 ? 4C 89 70 ? 55 48 8D 68 ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 49 8B D9}
    MC void _renderHoverBox(MinecraftUIRenderContext*, IClientInstance*, RectangleArea*, float);
};
