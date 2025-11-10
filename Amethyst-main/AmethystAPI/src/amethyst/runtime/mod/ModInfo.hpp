#pragma once
#include <string>
#include <vector>
#include <format>
#include <filesystem>
#include <expected>

#include "amethyst/runtime/utility/Version.hpp"
#include "amethyst/runtime/mod/ModDependency.hpp"
#include "amethyst/runtime/mod/ModError.hpp"

namespace fs = std::filesystem;
namespace Amethyst {
class ModInfo {
public:
    std::string UUID;
    std::string Namespace;
    std::string Name;
    std::string LoggingName;
    std::string FriendlyName;
    Version Version;
    std::vector<std::string> Authors;
    std::vector<ModDependency> Dependencies;
    bool IsRuntime;
    fs::path Directory;
    std::string LibraryName;

    ModInfo() = delete;
    ModInfo(
        const std::string& uuid,
        const std::string& modnamespace,
        const std::string& name,
        const std::string& loggingName,
        const std::string& friendlyName,
        const Amethyst::Version& version,
        const std::vector<std::string>& authors,
        const std::vector<ModDependency>& dependencies,
        bool isRuntime,
        const fs::path& directory,
        const std::string& libraryName
    );

    ModInfo(const ModInfo& other) = default;
    ModInfo& operator=(const ModInfo& other) = default;
    ModInfo(ModInfo&& other) noexcept = default;
    ModInfo& operator=(ModInfo&& other) noexcept = default;

    std::string GetVersionedName() const;
    bool Equals(const ModInfo& other, bool compareVersions = true) const;
    bool IsSameMod(const ModInfo& other) const;

    bool operator==(const ModInfo& other) const;
    bool operator!=(const ModInfo& other) const;
    bool operator<(const ModInfo& other) const;

    static std::expected<ModInfo, ModError> FromFile(const fs::path& jsonFile);
};
} // namespace Amethyst

namespace std {
    template<>
    struct hash<Amethyst::ModInfo> {
        size_t operator()(const Amethyst::ModInfo& modInfo) const {
            size_t h = hash<std::string>{}(modInfo.UUID);
            h ^= hash<std::string>{}(modInfo.Namespace) + 0x9e3779b9 + (h << 6) + (h >> 2);
            h ^= hash<std::string>{}(modInfo.Version.to_string()) + 0x9e3779b9 + (h << 6) + (h >> 2);
            return h;
        }
    };
} // namespace std