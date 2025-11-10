/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src/common/world/containers/managers/controllers/CraftingContainerController.hpp>

class ContainerModel;

/// @vptr {0x4DE7AF8}
class CreativeContainerController : public CraftingContainerController  {
public:
    /// @vidx {0}
    MC virtual ~CreativeContainerController() override;

    /// @vidx {2}
    MC virtual bool canRemove(int unk0, int unk1) const override;

    /// @vidx {4}
    MC virtual bool isItemFiltered(const Recipes& unk0, const ItemStackBase& unk1) const override;

    /// @vidx {5}
    MC virtual int getBackgroundStyle(int unk0, bool unk1) const override;

//begin members:
    /// @signature {48 89 5C 24 ? 48 89 4C 24 ? 56 57 41 56 48 83 EC ? 4C 8B F2 48 8B F9 E8 ? ? ? ? 4C 8B 00 BA ? ? ? ? 48 8B C8 49 8B 40 ? FF 15 ? ? ? ? 48 8B D8 48 85 C0 75 ? 48 C7 44 24 ? ? ? ? ? 48 8D 05 ? ? ? ? 48 89 44 24 ? 4C 8D 0D ? ? ? ? 44 8D 43 ? 48 8D 15 ? ? ? ? 48 8D 0D ? ? ? ? E8 ? ? ? ? 84 C0 74 ? C7 04 25 ? ? ? ? ? ? ? ? 48 89 9C 24}
    //MC CreativeContainerController* $ctor(CreativeContainerController*, std::shared_ptr<ContainerModel>);

	// Was inlined directly into std::make_shared
	CreativeContainerController(std::shared_ptr<ContainerModel> containerModel) 
		: CraftingContainerController(containerModel, false) {}

	// MC CreativeContainerController(std::shared_ptr<ContainerModel> containerModel);
};

//static_assert(sizeof(CreativeContainerController) == 88);