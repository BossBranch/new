/// @symbols
#pragma once 
#include <amethyst/Imports.hpp>
#include <mc/src/common/world/actor/ActorFlags.hpp>

class EntityContext;

namespace SynchedActorDataAccess {
	/// @sig {4C 8B 41 ? 4C 8B D1 48 8B 41 ? 4C 8B 49 ? 49 2B C0 48 C1 F8 ? 48 FF C8 25 ? ? ? ? 49 8B 0C C0 48 83 F9 ? 74 ? 0F 1F 84 00 ? ? ? ? 48 C1 E1 ? 42 81 7C 09 ? ? ? ? ? 4A 8D 04 09 74 ? 48 8B 08 48 83 F9 ? 75 ? 49 8B 42 ? 49 3B 42 ? 74 ? 48 8B 48 ? 48 85 C9 74 ? 4C 8B 49 ? 8B 02 8B D0 48 8B 49 ? 81 E2 ? ? ? ? 49 2B C9 44 8B C2 49 C1 E8 ? 48 C1 F9 ? 4C 3B C1 73 ? 4B 8B 0C C1 48 85 C9 74 ? 81 E2 ? ? ? ? 4C 8D 04 91 4D 85 C0 74 ? 25 ? ? ? ? 41 33 00 3D ? ? ? ? 73 ? B0 ? C3 32 C0 C3 CC CC CC CC CC CC CC CC CC CC CC CC CC CC CC 48 3B CA}
	MC bool getActorFlag(const EntityContext& entity, ActorFlags flag);

	/// @sig {48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 8B 41 ? 8B EA 48 8B F9}
	MC void setActorFlag(EntityContext& entity, ActorFlags flag, bool value);
}