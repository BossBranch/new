#pragma once
#include <string>

#include "amethyst/runtime/utility/Version.hpp"

namespace Amethyst {
class ModInfo;
class ModDependency {
public:
    std::string UUID;
    std::string Namespace;
    std::string RangeString;
    Range Range;
    bool IsSoft;

    ModDependency() = delete;
    ModDependency(
        const std::string& uuid,
        const std::string& modNamespace,
        const std::string& range,
        bool isSoft
    );

    ModDependency(const ModDependency& other) = default;
    ModDependency& operator=(const ModDependency& other) = default;
    ModDependency(ModDependency&& other) noexcept = default;
    ModDependency& operator=(ModDependency&& other) noexcept = default;

    bool IsNamespaceDependency() const;
    bool Equals(const ModDependency& other) const;
    bool MatchesMod(const ModInfo& mod, bool checkVersion = true) const;
    bool MatchesVersion(const Version& version) const;
    std::string GetDependencyIdentification() const;

    bool operator==(const ModDependency& other) const;
    bool operator!=(const ModDependency& other) const;
    bool operator<(const ModDependency& other) const;
};
} // namespace Amethyst