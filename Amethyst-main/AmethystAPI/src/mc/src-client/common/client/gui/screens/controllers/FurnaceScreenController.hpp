/// @symbols
#pragma once
#include "mc/src-client/common/client/gui/screens/controllers/ContainerScreenController.hpp"

class FurnaceContainerManagerController;

/** @vptr {48 8D 05 ? ? ? ? 48 89 07 48 8D 05 ? ? ? ? 48 89 87 ? ? ? ? 4C 89 A7 ? ? ? ? 4C 89 A7 ? ? ? ? C6 87} */
class FurnaceScreenController :
	public ContainerScreenController
{
public:
	MC static uintptr_t $vtable_for_this;

	std::shared_ptr<FurnaceContainerManagerController> mFurnaceContainerManagerController;
	ContainerEnumName mHoveredContainer;
	const ContainerEnumName mIngredientName;

	/** @sig {48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B F9 4C 8B F2} */
	MC FurnaceScreenController(std::shared_ptr<ClientInstanceScreenModel> model, Player& player, const BlockPos& pos, ActorUniqueID actorId, const HashedString& tag);

	/** @vidx {i} */ MC virtual ~FurnaceScreenController() override;
	/** @vidx {i} */ MC virtual ui::DirtyFlag tick() override;
	/** @vidx {i} */ MC virtual bool _isStillValid(void) override;
	/** @vidx {i} */ MC virtual ui::ViewRequest _onContainerSlotHovered(const std::string& collection, int index) override;
	/** @vidx {i} */ MC virtual void _registerCoalesceOrder() override;
	/** @vidx {i} */ MC virtual void _registerAutoPlaceOrder() override;
};

static_assert(sizeof(FurnaceScreenController) - sizeof(ContainerScreenController) == 24, "Size of FurnaceScreenController doesn't match what's expected.");