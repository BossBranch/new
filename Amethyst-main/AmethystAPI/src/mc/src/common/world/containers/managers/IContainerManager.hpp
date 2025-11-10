#pragma once
#include "mc/src/common/world/Container.hpp"

class ContainerScreenContext;

class IContainerManager {
public:
    virtual ~IContainerManager() = 0;
    virtual ContainerID getContainerId() = 0;
    virtual void setContainerId(ContainerID id) = 0;
    virtual ContainerType getContainerType() = 0;
    virtual void setContainerType(ContainerType type) = 0;
    virtual void serverInitItemStackIds() = 0;
    virtual std::vector<ItemStack> getItemCopies() const = 0;
    virtual void setSlot(int slot, const ItemStack& stack, bool) = 0;
    virtual const ItemStack& getSlot(int slot) const = 0;
    virtual void setData(int, int) = 0;
    virtual void broadcastChanges() = 0;
    virtual void debitPlayerLevels(int amount) = 0;
    virtual bool isCreativeMode() = 0;
    virtual bool isClientSide() = 0;
    virtual bool isServerAuthoritative() = 0;
    virtual bool isValid(float) = 0;
    virtual int tick() = 0;
    virtual ContainerScreenContext _postInit() = 0;
};