/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>

class ScreenContext;
class Tessellator;

namespace mce {
class MaterialPtr;
}

class Tessellator;

namespace MeshHelpers {
/// @signature {48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 49 8B F8 48 8B DA 48 8B F1 80 BA}
MC void renderMeshImmediately(ScreenContext& screenContext, Tessellator& tessellator, const mce::MaterialPtr& material);
};