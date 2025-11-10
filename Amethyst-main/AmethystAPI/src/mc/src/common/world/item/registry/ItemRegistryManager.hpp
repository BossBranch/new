/// @symbolgeneration
#pragma once
#include "mc/src/common/world/item/registry/ItemRegistryRef.hpp"
#include <amethyst/Imports.hpp>

class ItemRegistryManager {
public:
    /// @signature {40 53 48 83 EC ? 48 83 3D ? ? ? ? ? 48 8B D9 74}
    MC static ItemRegistryRef getItemRegistry();
};