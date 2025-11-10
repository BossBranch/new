#pragma once

#include "mc/src-deps/gamerefs/GameRefs.hpp"
#include "mc/src-deps/gamerefs/StackRefResult.hpp"

template <class T>
class WeakRef : public GameRefs<T>::WeakStorage {
public:
    using Base = GameRefs<T>::WeakStorage;
    using Base::Base;

    constexpr WeakRef(GameRefs<T>::StackResultStorage const& ptr) : Base(ptr) {}
    constexpr WeakRef(Base const& ptr) : Base(ptr) {}
    constexpr WeakRef(Base&& ptr) : Base(std::move(ptr)) {}

    constexpr StackRefResult<T> lock() const {
        if constexpr (requires(Base t) { t.lock(); }) {
            return StackRefResult<T>{this->Base::lock()};
        } else {
            return StackRefResult<T>{*this};
        }
    }

	T* get() const {
		auto sp = this->Base::lock();
		return sp ? sp.get() : nullptr;
    }

	T& operator*() const { return *get(); }
    T* operator->() const { return get(); }

	constexpr bool operator!() const noexcept {
		return !get();
	}

	constexpr explicit operator bool() const noexcept {
		return get() != nullptr;
	}
};