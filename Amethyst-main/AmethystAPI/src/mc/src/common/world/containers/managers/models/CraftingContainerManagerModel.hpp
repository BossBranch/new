///@symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>
// #include <mc/src-unknown/ContainerID.hpp>
#include <mc/src/common/world/item/ItemInstance.hpp>
#include <mc/src/common/world/containers/managers/models/ContainerManagerModel.hpp>
#include <mc/src/common/world/containers/managers/IContainerManager.hpp>
#include <mc/src/common/world/containers/managers/models/FilterResult.hpp>

class FilteredContainerModel;
class CreativeItemGroupCategory;

/// @vptr {0x4DE98E0}
class CraftingContainerManagerModel : public ContainerManagerModel {
public:
	/// @vidx {i}
	MC virtual ~CraftingContainerManagerModel();

	/// @vidx {i}
	MC virtual std::vector<ItemStack> getItemCopies() const override;

	/// @vidx {i}
	MC virtual void setSlot(int unk0, const ItemStack& unk1, bool unk2) override;

	/// @vidx {i}
	MC virtual const ItemStack& getSlot(int unk0) const override;

	/// @vidx {i}
	MC virtual void setData(int unk0, int unk1) override;

	/// @vidx {i}
	MC virtual void broadcastChanges() override;

	/// @vidx {i}
	MC virtual int tick() override;

	/// @vidx {i}
	MC virtual bool isValid(float unk0) override;

	/// @vidx {i}
	MC virtual ContainerScreenContext _postInit() override;

//begin members:
    MC static uintptr_t $vtable_for_this;

	// CraftingContainerManagerModel(ContainerID, Player&, bool, bool, bool, const BlockPos&, const std::string&);

	// UnknownReturn getBlockPos() const;

	// UnknownReturn getCraftingTags() const;

	// UnknownReturn getCursorSelectedItem() const;

	// UnknownReturn getGridSize() const;

	// UnknownReturn getSearchString() const;

	// UnknownReturn setIsFiltering(bool unk0);

	// UnknownReturn setLastCraftedItem(const ItemInstance& unk0);

	// UnknownReturn setSearchString(const std::string& unk0);

	// UnknownReturn hasIngredientSetChanged(const ItemStack& unk0);

	/// @signature {44 88 44 24 ? 53 55 56 57 41 56 48 81 EC ? ? ? ? 0F 29 B4 24}
	MC std::shared_ptr<FilteredContainerModel> _createContainerModel(ContainerEnumName unk0, CreativeItemGroupCategory* unk1, bool unk2, std::function<FilterResult(const ItemInstance&, bool)> unk3);

	// UnknownReturn _createContainerModel(ContainerEnumName unk0, const std::vector<ItemInstance>& unk1, bool unk2, std::function<FilterResult(const ItemInstance&, bool)> unk3);

	// UnknownReturn _filterByInventory(const ItemInstance& unk0, bool unk1) const;

	// UnknownReturn _filterByText(const ItemInstance& unk0, TextSearchMode unk1) const;

	// UnknownReturn _filterByTextAndInventory(const ItemInstance& unk0, bool unk1, TextSearchMode unk2) const;

	// UnknownReturn _foundInStartOfAnyWord(const std::string& unk0) const;

	// UnknownReturn _getCaseFoldedSearchString() const;

	// UnknownReturn _getCreativeItemRegistry() const;

	// UnknownReturn _hasUnlockedRecipes(const ItemInstance& unk0) const;

	// UnknownReturn _isWorkbenchValid() const;

	// UnknownReturn _shouldItemBeHiddenIfLocked(const ItemInstance& unk0) const;

	// UnknownReturn fireItemAcquiredEvent(const ItemInstance& unk0, int unk1);

	// UnknownReturn fireItemCraftedEvent(const ItemInstance& unk0, bool unk1, bool unk2, int unk3, int unk4, int unk5, bool unk6, bool unk7, const std::vector<short>& unk8);
};


