/// @symbolgeneration
#pragma once
#include <shared_mutex>
#include "amethyst/Imports.hpp"
#include "mc/src-deps/core/utility/NonOwnerPointer.hpp"
#include "mc/src/common/options/AppConfigs.hpp"

template <typename T>
class ServiceLocator {
public:
    static Bedrock::NonOwnerPointer<T> mService;
};

template <>
class ServiceLocator<AppConfigs> {
public:
    /// @address {0x5A4B9C8}
    MC static std::shared_mutex mMutex;
    /// @address {0x5A4BA38}
    MC static Bedrock::NonOwnerPointer<AppConfigs> mService;

};