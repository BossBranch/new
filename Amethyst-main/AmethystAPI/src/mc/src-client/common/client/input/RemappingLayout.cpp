#include "mc/src-client/common/client/input/RemappingLayout.hpp"

const Keymapping* RemappingLayout::getKeymappingByAction(const std::string& actionName) const {
    for (auto& keymapping : mKeymappings) {
        if (keymapping.mAction == actionName) return &keymapping;
    }

    return nullptr;
}

Keymapping* RemappingLayout::getKeymappingByAction(const std::string& actionName)
{
    for (auto& keymapping : mKeymappings) {
        if (keymapping.mAction == actionName) return &keymapping;
    }

    return nullptr;
}
