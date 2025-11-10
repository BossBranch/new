/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>

#include <mc/src/common/world/item/CreativeItemCategory.hpp>
#include <mc/src/common/world/inventory/InventoryOptions.hpp>
#include <mc/src/common/world/containers/ContainerEnumName.hpp>
#include <mc/src/common/world/item/ItemInstance.hpp>
#include <mc/src-client/common/client/gui/screens/controllers/ContainerScreenController.hpp>

enum class CategoryTabState : uint32_t { // guessed size
    Test
};

/// @vptr {0x4CD23F8}
class CraftingScreenController : public ContainerScreenController {
public:
    struct CategoryTabInfo {
    public:
        CreativeItemCategory mCategory; 
        uint32_t mCategoryBitmaskIndex; // The game stores tabs as a uint32_t, it uses 1 << mCategoryBitmaskIndex as a flag for the tab
        ContainerEnumName mContainerEnum;
        std::string mTabName;
        std::string mTabFactoryName;
    };

public:
    std::byte padding0[4536 - sizeof(ContainerScreenController)]; 
    ItemInstance instance4536;
    uint64_t padding4672;
    uint32_t something;

    /* this + 4684 */ std::byte padding4684[4796 - 4684];
    /* this + 4796 */ uint32_t mSomething;
    /* this + 4800 */ std::byte padding4800[4848 - 4800];

    ItemInstance instance4848;
    uint64_t padding4984;

    std::unordered_map<InventoryLeftTabIndex, CategoryTabState> mTabStates;

    MC static uintptr_t $vtable_for_this;

    

    /// @address {0x5A38174}
    MC static uint32_t mTabsWaitingToBeAnimatedIn;

    /// @address {0x59BF778}
    MC static std::vector<CategoryTabInfo> mCategoryTabs;

    /// @vidx {i}
    MC virtual std::string _getCollectionName(UIPropertyBag*);

    /// @signature {48 89 5C 24 ? 44 89 44 24 ? 55 56 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 41 8B F8}
    MC std::string _tabIndexToCollectionName(InventoryLeftTabIndex tabIdx) const;

    /// @signature {48 89 5C 24 ? 55 56 57 41 56 41 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 45 8B F8 48 8B DA 4C 8B F1}
    MC void _focusCollectionItem(const std::string& item, int unkn1);

    /// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 0F 29 B4 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 45 8B E1}
    MC void _showCategoryTab(const CategoryTabInfo& tabInfo, bool someBool, int someInt);

    /// @sig {40 55 53 56 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? B8 ? ? ? ? E8 ? ? ? ? 48 2B E0 48 8B D9 4C 8D 35 ? ? ? ? 4C 89 B5 ? ? ? ? 48 8D 85 ? ? ? ? 48 89 85 ? ? ? ? 48 8D 05 ? ? ? ? 48 89 85 ? ? ? ? 48 89 8D ? ? ? ? 48 8D 85 ? ? ? ? 48 89 85 ? ? ? ? 48 8D 85}
    MC void _registerBindings();

    /// @signature {48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 54 41 55 41 56 41 57 48 83 EC ? 48 8B F1 48 8B 89}
    MC void _updateCategoryTabs(); 

    /// @signature {40 53 48 83 EC ? 8B 81 ? ? ? ? 48 8B D9 85 C0 7E ? FF C8 89 81 ? ? ? ? 33 C0}
    MC uint32_t _updateCategoryTabsByRecipes();
};

static_assert(offsetof(CraftingScreenController, something) == 4680);
static_assert(offsetof(CraftingScreenController, mTabStates) == 4992);
static_assert(offsetof(CraftingScreenController, mSomething) == 4796);