#pragma once
#include <mc/src-deps/gamerefs/gamerefs_shareptr/OwnerStorageSharePtr.hpp>
#include <mc/src-deps/gamerefs/gamerefs_shareptr/WeakStorageSharePtr.hpp>
#include <mc/src-deps/gamerefs/gamerefs_shareptr/StackResultStorageSharePtr.hpp>

template <typename T>
struct GameRefs {
	using OwnerStorage       = OwnerStorageSharePtr<T>;
    using StackResultStorage = StackResultStorageSharePtr<T>;
    using WeakStorage        = WeakStorageSharePtr<T>;
    using StackRef           = T;
};