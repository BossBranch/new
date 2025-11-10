#pragma once
#include <mc/src/common/world/item/CreativeItemCategory.hpp>
#include <mc/src/common/world/item/registry/ItemRegistryRef.hpp>

class Block;
class BlockLegacy;
class ItemInstance;

namespace Amethyst {
class SharedContext;

/**
 * An instance of a creative item category, each category is a tab in the creative inventory
 */
class CreativeCategory {
public:
    void AddCreativeItem(const BlockLegacy& block);
    void AddCreativeItem(const Block& block);

private:
    CreativeCategory(const CreativeCategory&) = delete;
    CreativeCategory& operator=(const CreativeCategory&) = delete;

    CreativeItemCategory mInternalCategory;
    std::vector<const Block*> mItemsToRegister;

    /// Internal do NOT call
    void _Reset();

public:
    /// Use CreativeItemRegistry to get the instances of this, do NOT construct manually
    CreativeCategory(CreativeItemCategory category);

    /// Internal do NOT use
    void _RegisterItems(ItemRegistryRef ref);
};

/**
 * A registry for adding creative items to the game without worrying about timings
 * eventually will support creating custom item categories too.
 */
class CreativeItemRegistry {
public:
    CreativeCategory& GetVanillaCategory(CreativeItemCategory vanillaCategory);

private:
    CreativeItemRegistry();
    CreativeItemRegistry(const CreativeItemRegistry&) = delete;
    CreativeItemRegistry& operator=(const CreativeItemRegistry&) = delete;

    std::unordered_map<CreativeItemCategory, std::unique_ptr<CreativeCategory>> mCategories;

    friend class Amethyst::SharedContext;
};

}