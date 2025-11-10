/// @symbolgeneration
#pragma once
#include "mc/src/common/ActorUniqueID.hpp"
#include "mc/src/common/world/level/BlockPos.hpp"
#include "mc/src-client/common/client/gui/screens/controllers/ContainerScreenController.hpp"
#include "mc/src/common/world/item/ItemInstance.hpp"
#include "mc/src/common/world/Container.hpp"

class SparseContainer;
class Container;

enum class ContainerCategory : int {
    Default = 0x0000,
    PlayerInventory = 0x0001,
    Intermediary = 0x0002,
    Output = 0x0003,
    Unknown = 0x0004,
};

enum ContainerExpandStatus : int {
    Normal = 0x0000,
    Expanded = 0x0001,
    Contracted = 0x0002,
    Child = 0x0003,
    Count = 0x0004,
};

enum class ActorContainerType : int {
    Armor = 0x0000,
    Hand = 0x0001,
    ContainerComponent = 0x0002,
    PlayerUI = 0x0003,
    PlayerInventory = 0x0004,
    PlayerEnderChest = 0x0005,
};

class ContainerWeakRef {
public:
    ActorUniqueID mContainerActor;
    ActorContainerType mActorContainerType;
    BlockPos mBlockPosition;
    uint32_t mContainerRuntimeId; // <- actually a TypedRuntimeId<ContainerRuntimeIdTag, unsigned int, 0>

    /// @signature {48 83 EC ? 4C 8B D9 83 FA ? 0F 87}
    MC static Container* tryGetActorContainer(Actor& actor, ActorContainerType type);
};

/// @vptr {0x4DE9508}
class ContainerModel : 
	public ContainerContentChangeListener 
{
public:
    MC static uintptr_t $vtable_for_this;

    const bool mIsClientSide;
    std::string mContainerStringName;
    const ContainerEnumName mContainerEnumName;
    std::vector<std::function<void(int, const ItemStack&, const ItemStack&)>> mOnContainerChangedCallbacks;
    std::function<void(int, const ItemStack&, const ItemStack&)> mPlayerNotificationCallbacks;
    ContainerCategory mContainerCategory;
    std::vector<SlotData> mItemSource;
    SparseContainer* mClientUIContainer;
    std::vector<ItemStack> mItems;

    /// @signature {48 89 5C 24 ? 48 89 6C 24 ? 48 89 4C 24 ? 56 57 41 56 48 83 EC ? 48 8B D9 48 8D 05}
    MC ContainerModel(ContainerEnumName, int, ContainerCategory, bool);

    /// @vidx {0}
    MC virtual void containerContentChanged(int);
    /// @vidx {1}
    MC virtual ~ContainerModel();
    /// @vidx {2}
    MC virtual void postInit();
    /// @vidx {3}
    MC virtual void releaseResources();
    /// @vidx {4}
    MC virtual int getContainerSize();
    /// @vidx {5}
    MC virtual int getFilteredContainerSize();
    /// @vidx {6}
    MC virtual void tick(int);
    /// @vidx {7}
    MC virtual ContainerWeakRef getContainerWeakRef();
    /// @vidx {8}
    MC virtual const ItemStack& getItemStack(int slot);
    /// @vidx {9}
    MC virtual const std::vector<ItemStack>& getItems();
    /// @vidx {10}
    MC virtual const ItemInstance& getItemInstance(int slot);
    /// @vidx {11}
    MC virtual const ItemStackBase& getItemStackBase(int slot);
    /// @vidx {12}
    MC virtual bool isItemInstanceBased();
    /// @vidx {13}
    MC virtual void setItem(int slot, const ItemStack& stack);
    /// @vidx {14}
    MC virtual bool isValid();
    /// @vidx {15}
    MC virtual bool isItemFiltered(const ItemStackBase& stack);
    /// @vidx {16}
    MC virtual bool isExpanableItemFiltered(int slot);
    /// @vidx {17}
    MC virtual ContainerExpandStatus getItemExpandStatus(int slot);
    /// @vidx {18}
    MC virtual std::string getItemGroupName(int slot);
    /// @vidx {19}
    MC virtual void switchItemExpando(int slot);
    /// @vidx {20}
    MC virtual bool isSlotDisabled(int slot);
    /// @vidx {21}
    MC virtual Container* _getContainer();
    /// @vidx {22}
    MC virtual int _getContainerOffset();
    /// @vidx {23}
    MC virtual void _init();
    /// @vidx {24}
    MC virtual void _onItemChanged(int slot, const ItemStack& a, const ItemStack& b);

// Non-virtuals
public:
    /// @signature {85 D2 0F 88 ? ? ? ? 53 55 56 57 41 56 41 57}
    MC void networkUpdateItem(int, const ItemStack&, bool);

    MC const std::string& getContainerStringName() const {
        return mContainerStringName;
    }
};

static_assert(sizeof(ContainerModel) == 0xD0);