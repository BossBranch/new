/// @symbolgeneration
#pragma once
#include <memory>
#include "amethyst/Imports.hpp"

class SimpleSparseContainer;
class ContainerScreenContext;
class ContainerScreenValidatorBase {};
enum class ContainerEnumName : unsigned char;

class ContainerScreenValidation {
public:
    std::byte padding0[0x38];
    std::unordered_map<ContainerEnumName, uint64_t> mContainerIndexMap;

    /// @signature {48 89 5C 24 ? 48 89 7C 24 ? 55 48 8B EC 48 83 EC ? 33 FF}
    MC static std::unique_ptr<ContainerScreenValidatorBase> createContainerScreenValidator(const ContainerScreenContext& ctx);

    /// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 45 0F B6 F8 48 8B FA}
    MC std::shared_ptr<SimpleSparseContainer> getOrCreateSparseContainer(ContainerEnumName enumName);
};