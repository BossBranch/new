/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>
#include <map>

#include "mc/src-deps/core/string/StringHash.hpp"
#include "mc/src/common/world/item/crafting/Recipe.hpp"
#include "mc/src/common/world/item/ItemInstance.hpp"

class ResourcePackManager;
class ExternalRecipeStore;
class BaseGameVersion;
class Experiments;

struct FurnaceRecipeKey {
public:
	int mID;
	HashedString mTag;

	bool operator<(const FurnaceRecipeKey& other) const {
		return (mID < other.mID);
	}
};

class Recipes {
public:
    std::byte padding0[0x10];
	std::map<HashedString, std::map<std::string, std::shared_ptr<Recipe>>> mRecipes;
	std::map<FurnaceRecipeKey, ItemInstance> mFurnaceRecipes;

    /// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 4D 8B F1 4D 8B E0 4C 8B FA}
    MC void init(ResourcePackManager&, ExternalRecipeStore&, const BaseGameVersion&, const Experiments&);
};
