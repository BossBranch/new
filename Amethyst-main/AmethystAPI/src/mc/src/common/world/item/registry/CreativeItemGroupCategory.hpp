/// @symbols
#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src/common/world/item/CreativeItemCategory.hpp>

class CreativeItemRegistry;

class CreativeItemGroupCategory {
public:
    std::string mName;
    CreativeItemCategory mCategory;
    CreativeItemRegistry *mRegistry;
    std::unordered_map<HashedString, uint32_t> mNamedGroupIndex;
    std::vector<uint32_t> mGroupIndexes;

    /// @signature {4C 8B 49 ? 33 C0 4D 85 C9}
    MC uint64_t getTotalNumberChildItems() const;
};