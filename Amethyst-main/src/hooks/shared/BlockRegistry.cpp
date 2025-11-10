#if defined(CLIENT) || defined(SERVER)
#include "hooks/shared/BlockRegistry.hpp"

#include <amethyst/runtime/utility/InlineHook.hpp>
#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/runtime/events/GameEvents.hpp>
#include <amethyst/runtime/events/RegisterEvents.hpp>

#include <mc/src/common/world/level/block/definition/BlockDefinitionGroup.hpp>
#include <mc/src/common/world/level/block/registry/BlockTypeRegistry.hpp>

namespace Amethyst::SharedHooks::BlockRegistryHooks {
	Amethyst::InlineHook<decltype(&BlockDefinitionGroup::registerBlocks)> _BlockDefinitionGroup_registerBlocks;
	void BlockDefinitionGroup_registerBlocks(BlockDefinitionGroup* self) {
		RegisterBlocksEvent event(*self);
		Amethyst::GetEventBus().Invoke(event);
		_BlockDefinitionGroup_registerBlocks(self);
	}

	void Initialize() {
		auto& hooks = Amethyst::GetHookManager();
		HOOK(BlockDefinitionGroup, registerBlocks);
	}
}
#endif