/// @symbolgeneration
#pragma once
#include <memory>
#include <string>
#include "mc/src/common/world/Container.hpp"
#include "mc/src/common/world/containers/SlotData.hpp"
#include "mc/src/common/world/item/ItemStack.hpp"
#include "amethyst/Imports.hpp"
// WIP?

class ContainerScreenActionResult;
class ItemStackRequestScope;
class AutoPlaceResult;
class ItemTransferAmount;
class ContainerManagerModel;
class ContainerController;
enum class ContainerScreenRequestActionType;

class AutoPlaceItem {
public:
    std::string collection;
    bool stopWhenPlaced;
};

class SelectedSlotInfo {
public:
    const SlotData& mSlot;
    const int mProgressiveTake;
};

enum ItemTakeType : int {
    All = 0x0000,
    Half = 0x0001,
    One = 0x0002,
};

enum ItemTransferType : int32_t {
	Take = 0x0000,
	Place = 0x0001,
	AddToExisting = 0x0002,
};

/// @vptr {0x4DE9D50}
class ContainerManagerController :
	public std::enable_shared_from_this<ContainerManagerController>
{
public:
    MC static uintptr_t $vtable_for_this;

    std::weak_ptr<ContainerManagerModel> mContainerManagerModel;
    std::unordered_map<std::string, std::shared_ptr<ContainerController>> mContainers;
    std::byte padding104[0x40];

    /// @signature {48 89 5C 24 ? 48 89 54 24 ? 48 89 4C 24 ? 55 56 57 48 83 EC ? 48 8B F2 48 8B D9}
    MC ContainerManagerController(std::weak_ptr<ContainerManagerModel>);

    /// @vidx {0}
    MC virtual ~ContainerManagerController();
    /// @vidx {1}
    MC virtual void postInit(std::weak_ptr<ContainerManagerController>);
    /// @vidx {2}
    MC virtual void registerContainerCallbacks(void);
    /// @vidx {3}
    MC virtual void setPreviewItemName(const std::string&);
    /// @vidx {4}
    MC virtual void setItemName(const std::string&);
    /// @vidx {5}
    MC virtual void getPreviewItemName(void);
    /// @vidx {6}
    MC virtual void getItemName(void);
    /// @vidx {7}
    MC virtual void updatePreviewItem(void);
    /// @vidx {8}
    MC virtual const ItemStackBase& getTakeableItemStackBase(const SlotData& slot);
    /// @vidx {9}
    MC virtual void handleTakeAmount(const SlotData&, int, const SlotData&);
    /// @vidx {10}
    MC virtual void handleTakeAll(const SlotData&, const SlotData&);
    /// @vidx {11}
    MC virtual void handlePlaceAll(const SelectedSlotInfo&, const SlotData&);
    /// @vidx {12}
    MC virtual void handleTakeHalf(const SlotData&, const SlotData&);
    /// @vidx {13}
    MC virtual void handlePlaceOne(const SlotData&, const SlotData&);
    /// @vidx {14}
    MC virtual void handlePlaceAmount(const SlotData&, int, const SlotData&);
    /// @vidx {15}
    MC virtual void handleAutoPlace(const SlotData&, int, const std::vector<AutoPlaceItem>&, std::vector<AutoPlaceResult>&);
    /// @vidx {16}
    MC virtual void handleAutoPlaceIntoItemContainer(const SlotData&, const SlotData&);
    /// @vidx {17}
    MC virtual void handleAutoPlaceStack(const SlotData&, ItemTakeType, std::vector<AutoPlaceItem> const&, std::vector<AutoPlaceResult>&);
    /// @vidx {18}
    MC virtual void handleSplitSingle(const SlotData&, const SlotData&);
    /// @vidx {19}
    MC virtual void handleSplitMultiple(SelectedSlotInfo const&, const ItemInstance&, const SlotData&);
    /// @vidx {20}
    MC virtual void handleCoalesce(const SlotData&, std::vector<std::string> const&, const std::string&);
    /// @vidx {21}
    MC virtual void handleSwap(const SlotData&, const SlotData&);
    /// @vidx {22}
    MC virtual void handleDrop(const SlotData&, ItemTransferAmount);

    // Keep your eyes open for overloads
    /// @vidx {24}
    MC virtual void handleDestroy(SelectedSlotInfo const&, ItemTransferAmount);
    /// @vidx {23}
    MC virtual void handleDestroy(const SlotData&, ItemTransferAmount);

    /// @vidx {25}
    MC virtual void handleConsume(const SlotData&, ItemTransferAmount);
    /// @vidx {26}
    MC virtual void handleAddToStack(const SlotData&, const SlotData&, ItemTakeType);
    /// @vidx {27}
    MC virtual void handlePlaceInItemContainer(const SlotData&, const SlotData&);
    /// @vidx {28}
    MC virtual void handleTakeFromItemContainer(const SlotData&, const SlotData&, ItemTakeType);
    /// @vidx {29}
    MC virtual void closeContainers(void);
    /// @vidx {30}
    MC virtual void isOutputSlot(const std::string&);
    /// @vidx {31}
    MC virtual void _onItemTransferredFrom(const ItemInstance&, const SlotData&);
    /// @vidx {32}
    MC virtual void _onItemTransferredTo(const ItemInstance&, const SlotData&);
    /// @vidx {33}
    MC virtual void _onItemAcquired(const ItemInstance&, const SlotData&);
    /// @vidx {34}
    MC virtual void _onItemPlaced(const ItemInstance&, const SlotData&);
    /// @vidx {35}
    MC virtual void _onContainerScreenAction(const ContainerScreenActionResult&);
    /// @vidx {36}
    MC virtual void _updateItemStackRequest(ContainerScreenRequestActionType, const ContainerScreenActionResult&, ItemStackRequestScope&);

    /** @sig {40 53 56 57 48 83 EC ? 48 83 7A ? ? 41 8B F0} */
    MC const ItemStack& getItemStack(const std::string& collectionName, int index);

	/** @sig {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B E1 4C 89 4C 24 ? 4D 8B F0} */
	MC bool _transfer(ItemTransferType type, const SlotData& srcSlot, const SlotData& dstSlot, ItemTransferAmount transferAmount, bool allowSwap, bool idk);
};

static_assert(sizeof(ContainerManagerController) == 0xA8);
//static_assert(offsetof(ContainerManagerController, mContainers) == 0x20);