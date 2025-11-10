#pragma once
#include <mc/src-deps/gamerefs/WeakRef.hpp>
#include <mc/src-deps/ecs/gamerefs_entity/GameRefsEntity.hpp>

class EntityContext;

class WeakEntityRef : public WeakRef<EntityContext> {
public:
	using Base = WeakRef<EntityContext>;
    using Base::Base;
    WeakEntityRef()                                = default;
    WeakEntityRef(WeakEntityRef&&)               = default;
    WeakEntityRef(WeakEntityRef const&)          = default;
    WeakEntityRef& operator=(const WeakEntityRef&) = default;
    WeakEntityRef& operator=(WeakEntityRef&&)      = default;
};