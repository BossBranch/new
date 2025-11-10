/// @symbolgeneration
#pragma once
#include "amethyst/Imports.hpp"
#include "mc/src/common/world/containers/models/ContainerModel.hpp"

enum class ContainerEnumName : unsigned char;
class Player;

/// @vptr {0x4DDF030}
class PlayerUIContainerModelBase :
    public ContainerModel 
{
public:
    MC static uintptr_t $vtable_for_this;

    Player& mPlayer;

    PlayerUIContainerModelBase(ContainerEnumName name, Player& player) : 
        ContainerModel(name, 1, ContainerCategory::Default, player.isClientSide()),
        mPlayer(player)
    {
        
    }

    /// @vidx {inherit}
    MC virtual void containerContentChanged(int);
    /// @vidx {inherit}
    MC virtual ~PlayerUIContainerModelBase();
    /// @vidx {inherit}
    MC virtual void postInit();
    /// @vidx {inherit}
    MC virtual void releaseResources();
    /// @vidx {inherit}
    MC virtual ContainerWeakRef getContainerWeakRef();
    /// @vidx {inherit}
    MC virtual bool isValid();
    /// @vidx {inherit}
    MC virtual Container* _getContainer();
    /// @vidx {inherit}
    MC virtual int _getContainerOffset();
    /// @vidx {inherit}
    MC virtual void _onItemChanged(int, const ItemStack&, const ItemStack&);
};

/// @vptr {0x4DE7600}
class PlayerUIContainerModel : 
    public PlayerUIContainerModelBase
{
public:
    PlayerUIContainerModel(ContainerEnumName name, Player& player) : 
        PlayerUIContainerModelBase(name, player)
    {
    }

    /// @vidx {inherit}
    MC virtual ~PlayerUIContainerModel();
    /// @vidx {inherit}
    MC virtual int _getContainerOffset();
};

static_assert(sizeof(PlayerUIContainerModelBase) == 0xD8);
static_assert(sizeof(PlayerUIContainerModel) == 0xD8);