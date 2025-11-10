/// @symbols
#pragma once
#include <amethyst/Imports.hpp>
#include <vector>
#include <memory>
#include <mc/src-client/common/client/input/RemappingLayout.hpp>

using KeyboardRemappingLayout = RemappingLayout;

class Options {
public:
    /* this + 0000 */ std::byte padding0[6256];
    /* this + 6256 */ std::vector<std::shared_ptr<KeyboardRemappingLayout>> mKeyboardRemappings;

    void* _readKeyboardMapping(char* a2, char* a3);

    /*
     * This is actually a virtual function, but it's at index 106, and I'm too lazy to add filler vfuncs
     */
    /** @sig {48 89 5C 24 ? 57 48 83 EC ? 48 8B 01 48 8B DA 41 B8} */
    MC std::shared_ptr<KeyboardRemappingLayout> getCurrentKeyboardRemapping() const;
};