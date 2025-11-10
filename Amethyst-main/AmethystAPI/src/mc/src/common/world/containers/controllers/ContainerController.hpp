/// @symbolgeneration
#pragma once
#include <memory>
#include "amethyst/Imports.hpp"
#include "mc/src/common/world/containers/models/ContainerModel.hpp"

class ContainerScreenContext;
class Recipes;
class ItemStackBase;
class ItemTransferAmount;

enum class ItemSetType : int {
    Place = 0x0000,
    Swap = 0x0001,
    Add = 0x0002,
    None = 0x0003,
};

enum class ItemAddType : int {
    All = 0x0000,
    Partial = 0x0001,
    None = 0x0002,
};

/// @vptr {0x4DE7760}
class ContainerController {
public:
    std::weak_ptr<ContainerModel> mContainerModel;
    bool mDrop;

    ContainerController(std::weak_ptr<ContainerModel> model, bool drop) : 
        mContainerModel(model), mDrop(drop) {}

    /// @vidx {0}
    MC virtual ~ContainerController();
    /// @vidx {1}
    MC virtual void* getRecipeItem(int) const; // probably returns ItemStack or ItemStackBase
    /// @vidx {2}
    MC virtual bool canRemove(int, int) const;
    /// @vidx {3}
    MC virtual bool isItemAllowed(const ItemStackBase&);
    /// @vidx {4}
    MC virtual bool isItemFiltered(const Recipes&, const ItemStackBase&) const;
    /// @vidx {5}
    MC virtual int getBackgroundStyle(int, bool) const;
    /// @vidx {6}
    MC virtual ItemSetType _canSet(const ContainerScreenContext&, int, const ItemStackBase&, ItemTransferAmount);
    /// @vidx {7}
    MC virtual int _getAvailableSetCount(const ContainerScreenContext&, int, const ItemStackBase&);
    /// @vidx {8}
    MC virtual bool _canRemove(int, int);
    /// @vidx {9}
    MC virtual void _onItemChanged(int);

    /// @signature {40 53 48 83 EC ? 48 8B 51 ? 45 33 C0}
    MC const std::string& getContainerName() const;
};