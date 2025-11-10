#pragma once
#include <mc/src-deps/gamerefs/gamerefs_shareptr/OwnerStorageSharePtr.hpp>

template <typename T>
struct SharePtrRefTraits {
    typedef T StackRef;
    typedef OwnerStorageSharePtr<T> OwnerStorage;
    typedef SharePtrRefTraits<T>::StackRef OwnerStackRef;
};