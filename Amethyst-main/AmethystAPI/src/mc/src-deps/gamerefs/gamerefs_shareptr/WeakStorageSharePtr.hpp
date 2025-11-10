#pragma once

template <typename T>
class WeakStorageSharePtr {
public:
	std::weak_ptr<T> mHandle;

	T* get() const {
		auto sp = mHandle.lock();
		return sp ? sp.get() : nullptr;
	}

	std::shared_ptr<T> lock() const {
        return mHandle.lock();
    }
};