#include "CreativeItemRegistry.hpp"
#include <amethyst/Log.hpp>
#include <mc/src/common/world/level/block/Block.hpp>
#include <mc/src/common/world/level/block/BlockLegacy.hpp>
#include <mc/src/common/world/item/Item.hpp>

void Amethyst::CreativeCategory::AddCreativeItem(const BlockLegacy& block)
{
    mItemsToRegister.push_back(block.mDefaultState);
}

void Amethyst::CreativeCategory::AddCreativeItem(const Block& block)
{
    mItemsToRegister.push_back(block.mLegacyBlock->mDefaultState);
}

Amethyst::CreativeCategory::CreativeCategory(CreativeItemCategory category)
    : mInternalCategory(category) {}

void Amethyst::CreativeCategory::_RegisterItems(ItemRegistryRef ref)
{
    for (auto block : mItemsToRegister) {
        Item::addCreativeItem(ref, *block);
    }

    _Reset();
}

void Amethyst::CreativeCategory::_Reset()
{
    mItemsToRegister.clear();
}

Amethyst::CreativeItemRegistry::CreativeItemRegistry()
{
    mCategories[CreativeItemCategory::Construction] = std::make_unique<CreativeCategory>(CreativeItemCategory::Construction);
    mCategories[CreativeItemCategory::Nature] = std::make_unique<CreativeCategory>(CreativeItemCategory::Nature);
    mCategories[CreativeItemCategory::Equipment] = std::make_unique<CreativeCategory>(CreativeItemCategory::Equipment);
    mCategories[CreativeItemCategory::Items] = std::make_unique<CreativeCategory>(CreativeItemCategory::Items);
    mCategories[CreativeItemCategory::ItemCommandOnly] = std::make_unique<CreativeCategory>(CreativeItemCategory::ItemCommandOnly);
}

//void Amethyst::CreativeItemRegistry::_Reset() {
//    for (auto& category : mCategories) {
//        category.second->_Reset();
//    }
//}

Amethyst::CreativeCategory& Amethyst::CreativeItemRegistry::GetVanillaCategory(CreativeItemCategory vanillaCategory)
{
    Assert(vanillaCategory != CreativeItemCategory::All && vanillaCategory != CreativeItemCategory::Undefined && vanillaCategory != CreativeItemCategory::NumCategories, "Invalid vanilla creative categories.");
    Assert((int)vanillaCategory < (int)CreativeItemCategory::Undefined, "vanillaCategory is out of range!");
    return *mCategories.at(vanillaCategory);
}