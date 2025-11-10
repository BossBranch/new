/// @symbols
#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src/common/world/level/block/BlockState.hpp>
#include <mc/src/common/world/level/block/PillarAxis.hpp>

class VanillaStates {
public:
	/// @address {0x59E0AD0}
	MC static BlockStateVariant<::Facing::Axis> PillarAxis;

	/// @address {0x59DFC90}
	MC static BlockStateVariant<int> WeirdoDirection;

	/// @address {0x59DF870}
	MC static BlockStateVariant<int> FacingDirection;
};