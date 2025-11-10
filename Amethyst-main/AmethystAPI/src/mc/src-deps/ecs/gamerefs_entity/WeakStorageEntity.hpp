#pragma once
#include "mc/src-deps/gamerefs/WeakRef.hpp"
#include "mc/src/common/world/entity/EntityId.hpp"

class EntityRegistry;

class WeakStorageEntity {
public:
	WeakRef<EntityRegistry> mRegistry;
	EntityId mEntity;
};