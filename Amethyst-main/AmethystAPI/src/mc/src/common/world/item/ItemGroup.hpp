/// @symbols
#pragma once
#include <amethyst/Imports.hpp>
#include "ItemInstance.hpp"

class ItemGroup {
public:
    ItemInstance mItemTemplate;
    int mCount;

    /** @sig {48 89 5C 24 ? 55 56 57 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B DA 4C 8B F1 48 89 54 24} */
    MC ItemInstance getItemInstance() const;
};