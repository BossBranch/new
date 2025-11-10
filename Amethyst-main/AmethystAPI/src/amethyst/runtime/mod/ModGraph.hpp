#pragma once
#include <unordered_set>

#include "amethyst/runtime/mod/ModRepository.hpp"
#include "amethyst/runtime/mod/ModInfo.hpp"

namespace Amethyst {
template <typename T>
struct StackGuard {
    std::vector<T>& mStack;
    T mValue;
    StackGuard(std::vector<T>& stack, T value) : 
        mStack(stack),
        mValue(value)
    {
        mStack.push_back(value);
    }

    ~StackGuard() {
        mStack.pop_back();
    }

    StackGuard(const StackGuard& other) = delete;
    StackGuard& operator=(const StackGuard& other) = delete;
    StackGuard(StackGuard&& other) noexcept = delete;
    StackGuard& operator=(StackGuard&& other) noexcept = delete;
};

class ModGraph {
    std::vector<std::shared_ptr<const ModInfo>> mMods;
    std::vector<ModError> mErrors;

public:
    ModGraph() = default;
    ~ModGraph() = default;

    ModGraph(const ModGraph& other) = delete;
    ModGraph& operator=(const ModGraph& other) = delete;
    ModGraph(ModGraph&& other) noexcept = delete;
    ModGraph& operator=(ModGraph&& other) noexcept = delete;

    void Clear();
    void SortAndValidate(const ModRepository& repository, const std::unordered_set<std::string>& profileMods);

    const std::vector<std::shared_ptr<const ModInfo>>& GetMods() const;
    const std::vector<ModError>& GetErrors() const;

    bool HasErrors() const;
    size_t GetModCount() const;
};
} // namespace Amethyst