#pragma once

#include "mc/src-deps/gamerefs/GameRefs.hpp"

template <typename T>
class OwnerPtr : public GameRefs<T>::OwnerStorage {
public:
    using Base = GameRefs<T>::OwnerStorage;
    using Base::Base;

    constexpr OwnerPtr(Base const& ptr) : Base(ptr) {}
    constexpr OwnerPtr(Base&& ptr) : Base(std::move(ptr)) {}

	T* get() const {
        return Base::get(); 
    }

	T& operator*() const { return *Base::get(); }
    T* operator->() const { return Base::get(); }
};