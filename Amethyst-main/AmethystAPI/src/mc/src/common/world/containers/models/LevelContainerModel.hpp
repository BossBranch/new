/// @symbolgeneration
#pragma once
#include "mc/src/common/world/containers/models/ContainerModel.hpp"
#include "mc/src/common/world/level/block/actor/BlockActorRendererId.hpp"

/// @vptr {0x4DDF378}
class LevelContainerModel : 
    public ContainerModel 
{
public:
    uintptr_t somethingIdk;
    Player& mPlayer;
    BlockPos mBlockPos;
    BlockActorType mBlockEntityType;
    ActorUniqueID mEntityUniqueId;
    
    /// @signature {48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B D9 49 8B F9 49 8B 89 ? ? ? ? 41 8B F0 0F B6 EA 48 85 C9 74 ? 48 8B 01 48 8B 80 ? ? ? ? FF 15 ? ? ? ? 84 C0 74 ? B0 ? 44 8B 4C 24 ? 44 8B C6 40 0F B6 D5 88 44 24 ? 48 8B CB E8 ? ? ? ? 48 8B 6C 24 ? 48 8D 05 ? ? ? ? 48 8B 74 24 ? 48 89 03 48 8D 05 ? ? ? ? 48 89 83 ? ? ? ? 48 8B 44 24}
    MC LevelContainerModel(ContainerEnumName enumName, int size, Player& player, BlockActorType type, const BlockPos& pos, ContainerCategory category);

    /// @vidx {inherit}
    MC virtual void containerContentChanged(int) override;
    /// @vidx {inherit}
    MC virtual ~LevelContainerModel() override;
    /// @vidx {inherit}
    MC virtual void postInit() override;
    /// @vidx {inherit}
    MC virtual void releaseResources() override;
    /// @vidx {inherit}
    MC virtual ContainerWeakRef getContainerWeakRef() override;
    /// @vidx {inherit}
    MC virtual bool isValid() override;
    /// @vidx {inherit}
    MC virtual bool isSlotDisabled(int slot) override;
    /// @vidx {inherit}
    MC virtual Container* _getContainer() override;
    /// @vidx {inherit}
    MC virtual int _getContainerOffset() override;
    /// @vidx {inherit}
    MC virtual void _onItemChanged(int slot, const ItemStack& a, const ItemStack& b) override;
    /// @vidx {25}
    MC virtual void containerRemoved();
};

static_assert(sizeof(LevelContainerModel) == 0xF8);