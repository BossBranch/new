#pragma once
#include <Windows.h>
#include <utility>

namespace Amethyst {
class ModuleHandle {
public:
    HMODULE hModule = nullptr;

    ModuleHandle() = default;
    ModuleHandle(HMODULE module) : 
        hModule(module) 
    {
    }

    ModuleHandle(const ModuleHandle&) = delete;
    ModuleHandle& operator=(const ModuleHandle&) = delete;
    ModuleHandle(ModuleHandle&& other) noexcept : 
        hModule(std::exchange(other.hModule, nullptr)) 
    {
    }

    ModuleHandle& operator=(ModuleHandle&& other) noexcept {
        if (this != &other) {
            if (hModule != nullptr)
                FreeLibrary(hModule);
            hModule = std::exchange(other.hModule, nullptr);
        }
        return *this;
    }

    void Reset(HMODULE module = nullptr) {
        if (hModule != nullptr)
            FreeLibrary(hModule);
        hModule = module;
    }

    ~ModuleHandle() {
        if (hModule != nullptr)
            FreeLibrary(hModule);
        hModule = nullptr;
    }

    bool IsValid() const {
        return hModule != nullptr;
    }

    operator bool() const {
        return IsValid();
    }

    HMODULE GetNative() const {
        return hModule;
    }

    operator HMODULE() const {
        return GetNative();
    }
};
} // namespace Amethyst