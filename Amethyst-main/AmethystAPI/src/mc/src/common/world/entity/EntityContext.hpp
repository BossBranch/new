#pragma once
#include "mc/src/common/world/entity/EntityId.hpp"

class EntityRegistry;

class EntityContext {
public:
    EntityRegistry& mRegistry;
    entt::basic_registry<EntityId>& mEnttRegistry;
    EntityId mEntity;

    [[nodiscard]] inline entt::basic_registry<EntityId>& getRegistry()
    {
        return mEnttRegistry;
    }

    [[nodiscard]] inline entt::basic_registry<EntityId> const& getRegistry() const
    {
        return mEnttRegistry;
    }

    template <typename Component>
    [[nodiscard]] inline Component& get()
    {
        return mEnttRegistry.get<Component>(mEntity);
    }

    template <typename Component>
    [[nodiscard]] inline Component* try_get()
    {
        return mEnttRegistry.try_get<Component>(mEntity);
    }

    template <typename Component>
    [[nodiscard]] inline Component const& get() const
    {
        return mEnttRegistry.get<Component>(mEntity);
    }
};