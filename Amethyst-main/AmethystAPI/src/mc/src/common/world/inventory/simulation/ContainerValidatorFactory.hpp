/// @symbolgeneration
#pragma once
#include "amethyst/Imports.hpp"

enum class ContainerEnumName : unsigned char;
class ContainerScreenContext;
class Container;

class ContainerValidatorFactory {
public:
    /// @signature {40 53 48 83 EC ? 0F B6 C1}
    MC static Container* getBackingContainer(ContainerEnumName name, const ContainerScreenContext& ctx);
};