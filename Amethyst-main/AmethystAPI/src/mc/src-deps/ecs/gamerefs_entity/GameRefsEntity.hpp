#pragma once
#include "mc/src/common/world/entity/EntityContext.hpp"
#include "mc/src-deps/ecs/gamerefs_entity/OwnerStorageEntity.hpp"
#include "mc/src-deps/ecs/gamerefs_entity/StackResultStorageEntity.hpp"
#include "mc/src-deps/ecs/gamerefs_entity/WeakStorageEntity.hpp"

template <>
struct GameRefs<EntityContext> {
    using OwnerStorage       = OwnerStorageEntity;
    using StackResultStorage = StackResultStorageEntity;
    using WeakStorage        = WeakStorageEntity;
    using StackRef           = EntityContext;
};

template <>
struct GameRefs<EntityContext const> {
    using OwnerStorage       = OwnerStorageEntity;
    using StackResultStorage = StackResultStorageEntity;
    using WeakStorage        = WeakStorageEntity;
    using StackRef           = EntityContext const;
};

template <>
struct GameRefs<EntityId> {
    using OwnerStorage       = OwnerStorageEntity;
    using StackResultStorage = StackResultStorageEntity;
    using WeakStorage        = WeakStorageEntity;
    using StackRef           = EntityContext;
};