/// @symbols
#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src/common/util/Factory.hpp>

class ILevel;
class Scheduler;
class Dimension;

namespace VanillaDimensionFactory {
	// Direct signature is bigger than 1kb lmfao
    /** @sig {E8 ? ? ? ? 49 8B 04 24 49 8B CC 48 8B 40 ? FF 15 ? ? ? ? 4C 8B F8} */
    MC void registerDimensionTypes(OwnerPtrFactory<Dimension, ILevel&, Scheduler&>& factory);
};