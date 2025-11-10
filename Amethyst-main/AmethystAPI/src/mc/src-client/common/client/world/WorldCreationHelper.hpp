/// @symbolgeneration
#pragma once
#include <string>
#include <mc/src/common/world/level/storage/LevelSummary.hpp>
#include <amethyst/Imports.hpp>

class WorldCreationHelper {
public:
	std::byte padding0[136];
	LevelSettings levelSettings; // 136
	std::string someString;
	uint64_t padding1512;
	PackIdVersion somePackId; // 1528
	LevelSummary levelSummary; // 1656

	/// @signature {48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 54 41 56 41 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 4D 8B F1 48 8B F9}
	MC void _WorldCreationHelper(void* a2, void* a3, void* a4, void* a5, void* a6, void* a7, void* a8, void* a9, void* a10, void* a11, void* a12); // args r obvs not accurate here
};
