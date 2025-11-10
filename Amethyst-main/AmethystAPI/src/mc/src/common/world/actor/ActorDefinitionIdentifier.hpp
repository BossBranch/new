/// @symbols
#pragma once
#include <string>
#include <amethyst/Imports.hpp>
#include <mc/src-deps/core/string/StringHash.hpp>
#include <mc/src/common/world/actor/ActorType.hpp>

struct ActorDefinitionIdentifier {
    std::string mNamespace;
    std::string mIdentifier;
    std::string mInitEvent;
    std::string mFullName;
    HashedString mCanonicalName;

	/// @signature {48 89 5C 24 ? 48 89 74 24 ? 48 89 4C 24 ? 57 48 83 EC ? 8B FA}
    MC ActorDefinitionIdentifier(ActorType actorType);
};
