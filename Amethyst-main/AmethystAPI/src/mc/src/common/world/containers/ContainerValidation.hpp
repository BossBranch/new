/// @symbolgeneration
#pragma once
#include "amethyst/Imports.hpp"

class SparseContainer;
enum class ContainerEnumName : unsigned char;
class ContainerScreenContext;

class ContainerValidation {
public:
    /// @signature {40 55 53 57 48 8B EC 48 81 EC ? ? ? ? 0F B6 FA}
    MC static void assignValidForSlotContainerDelegate(SparseContainer& container, ContainerEnumName enumName, const ContainerScreenContext& screenContext);
};