#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src-deps/core/utility/optional_ref.hpp>

class Actor;

class OwnerStorageEntity : public ::std::optional<::EntityContext> {
public:
    // template <class Entity = Actor, bool IncludeRemoved = false>
    // [[nodiscard]] optional_ref<Entity> tryUnwrap() const {
    //     if (*this) {
    //         return Entity::tryGetFromEntity(const_cast<EntityContext&>(**this), IncludeRemoved);
    //     }
    //     return nullptr;
    // }

	EntityContext* get() const {
		if (*this) {
			return const_cast<EntityContext*>(&**this);
		}
		return nullptr;
	}
};