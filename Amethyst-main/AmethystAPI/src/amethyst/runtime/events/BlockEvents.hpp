#pragma once
#include <amethyst/Imports.hpp>
#include "amethyst/runtime/events/EventBus.hpp"
#include "mc/src/common/world/Facing.hpp"

class Player;
class BlockPos;
class Block;
class Vec3;

class BeforeBlockUseEvent : public CancelableEvent {
public:
	Player& player;
	const BlockPos& pos;
	const Block& block;
	FacingID face;
	std::optional<Vec3> hitPos;

	BeforeBlockUseEvent(const Block& block, Player& player, const BlockPos& pos, FacingID face, const std::optional<Vec3>& hitPos)
		: player(player), pos(pos), block(block), face(face), hitPos(hitPos) {}
};