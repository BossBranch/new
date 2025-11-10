/// @symbolgeneration
#pragma once
#include "mc/src-client/common/client/gui/screens/controllers/ContainerScreenController.hpp"

class Player;
class BlockPos;
struct ActorUniqueID;
class ContainerManagerController;

/// @vptr {0x4EC2B90}
class BlockContainerScreenController :
	public ContainerScreenController 
{
public:
    std::shared_ptr<ContainerManagerController> mBlockContainerManagerController;

	/// @signature {48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 49 8B F1 48 8B FA 48 8B D9 48 89 4C 24}
    MC BlockContainerScreenController(std::shared_ptr<ClientInstanceScreenModel> model, Player& player, const BlockPos& pos, ActorUniqueID actorId);

	/// @vidx {inherit}
    MC virtual ~BlockContainerScreenController() override;
	/// @vidx {inherit}
    MC virtual bool _isStillValid() override;
    /// @vidx {inherit}
    MC virtual void _registerCoalesceOrder() override;
    /// @vidx {inherit}
    MC virtual void _registerAutoPlaceOrder() override;
};

static_assert(sizeof(BlockContainerScreenController) == 0x1168);