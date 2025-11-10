#include "Block.hpp"
#include <amethyst/runtime/utility/InlineHook.hpp>
#include <mc/src/common/world/level/block/Block.hpp>
#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/runtime/events/BlockEvents.hpp>

Amethyst::InlineHook<decltype(&Block::use)> _Block_use;

bool Block_use(Block* self, Player& player, const BlockPos& at, FacingID face, std::optional<Vec3> hit) {
	auto& bus = Amethyst::GetEventBus();
	BeforeBlockUseEvent event(*self, player, at, face, hit);
	bus.Invoke(event);

	if (event.IsCanceled()) return false;

	return _Block_use(self, player, at, face, hit);
}

void Amethyst::SharedHooks::BlockHooks::Initialize() {
	auto& hooks = Amethyst::GetHookManager();
	HOOK(Block, use);
}
