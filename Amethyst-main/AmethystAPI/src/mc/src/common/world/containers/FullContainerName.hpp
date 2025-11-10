/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src/common/world/containers/ContainerEnumName.hpp>

class FullContainerName {
public:
    ContainerEnumName mName;
    std::optional<uint32_t> mDynamicId;

    /// @signature {48 89 5C 24 ? 55 56 57 41 56 41 57 48 83 EC ? 4D 8B F0 48 8B FA 41 0F B6 10}
    MC std::string toString() const;
};