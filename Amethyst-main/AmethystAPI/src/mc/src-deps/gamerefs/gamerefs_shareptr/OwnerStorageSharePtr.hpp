#pragma once
#include <memory>
#include <cstddef>

template <typename T>
class OwnerStorageSharePtr {
public:
    std::shared_ptr<T> mValue;

    OwnerStorageSharePtr() = default;

    explicit OwnerStorageSharePtr(std::shared_ptr<T> ptr)
        : mValue(std::move(ptr)) {}

    OwnerStorageSharePtr(OwnerStorageSharePtr const&) = default;
    OwnerStorageSharePtr(OwnerStorageSharePtr&&) noexcept = default;
    OwnerStorageSharePtr& operator=(OwnerStorageSharePtr const&) = default;
    OwnerStorageSharePtr& operator=(OwnerStorageSharePtr&&) noexcept = default;

    T* get() const {
        return mValue.get();
    }

protected:
    bool _hasValue() const;
    void _reset();

    std::shared_ptr<T> _getShared() const {
        return mValue;
    }

    T& _getStackRef() const {
        return *mValue.get();
    }
};