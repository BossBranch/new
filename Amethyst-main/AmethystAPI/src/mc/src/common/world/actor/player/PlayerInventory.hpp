#pragma once
#include <functional>
#include "mc/src/common/world/item/ItemStack.hpp"
#include "mc/src/common/world/Container.hpp"

class Container;
class Inventory;
class HudContainerManagerModel;

class PlayerInventory : public ContainerSizeChangeListener, public ContainerContentChangeListener {
public:
    class SlotData {
    public:
        ContainerID mContainerId;
        int32_t mSlot;
    };

public:
    int32_t mSelected;
    ItemStack mInfiniteItem;
    ContainerID mSelectedContainerId;
    std::unique_ptr<Inventory> mInventory;
    std::vector<ItemStack> mComplexItems;
    std::weak_ptr<HudContainerManagerModel> mHudContainerManager;

    virtual ~PlayerInventory();
    virtual void createTransactionContext(
        std::function<void __cdecl(Container&, int, ItemStack const&, ItemStack const&)> callback,
        std::function<void __cdecl(void)> execute
    );

    const ItemStack& getSelectedItem() const;
    void setSelectedItem(const ItemStack& item);
};

//static_assert(offsetof(PlayerInventory, mInventory) == 224);