/// @symbolgeneration
#pragma once
#include "mc/src-client/common/client/gui/screens/controllers/BlockContainerScreenController.hpp"

enum class BlockActorType;

/// @vptr {0x4EC2B90}
class ChestScreenController : 
	public BlockContainerScreenController 
{
public:
    MC static uintptr_t $vtable_for_this;

	/// @signature {48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F2 48 8B F9 48 89 4C 24 ? 48 89 54 24 ? 0F 57 C0 F3 0F 7F 44 24 ? 48 8B 42 ? 48 85 C0 74 ? F0 FF 40 ? 48 8B 02 48 89 44 24 ? 48 8B 42 ? 48 89 44 24 ? 48 8B 9C 24 ? ? ? ? 48 89 5C 24 ? 48 8D 54 24 ? E8 ? ? ? ? 90 48 8D 05 ? ? ? ? 48 89 07 48 8D 05 ? ? ? ? 48 89 87 ? ? ? ? C6 87 ? ? ? ? ? 48 8D 54 24}
    MC ChestScreenController(std::shared_ptr<ClientInstanceScreenModel> model, Player& player, const BlockPos& pos, ActorUniqueID actorId, BlockActorType type);

	/// @vidx {inherit}
    MC virtual ~ChestScreenController() override;
	/// @vidx {inherit}
	MC virtual void _registerCoalesceOrder() override;
	/// @vidx {inherit}
    MC virtual void _registerAutoPlaceOrder() override;
};

static_assert(sizeof(ChestScreenController) == 0x1168);