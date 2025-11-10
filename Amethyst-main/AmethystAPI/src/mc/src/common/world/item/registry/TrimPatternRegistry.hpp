#pragma once
#include "mc/src/common/world/item/registry/TrimPattern.hpp"

class TrimPatternRegistry {
public:
    std::unordered_map<HashedString, HashedString> mTemplateItemToPatternIdMap;
    std::unordered_map<HashedString, HashedString> mPatternIdToTemplateItemMap;
};