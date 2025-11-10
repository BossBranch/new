/// @symbolgeneration
#pragma once
#include <functional>
#include "amethyst/Imports.hpp"

enum class ContainerEnumName : unsigned char;
class ItemStackBase;

class SparseContainer {
public:
    /// @signature {48 89 5C 24 ? 57 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 84 24 ? ? ? ? 49 8B D8 88 54 24 ? 48 89 5C 24 ? 49 83 78 ? ? 74 ? 48 81 C1 ? ? ? ? 4C 8D 44 24 ? 48 8D 54 24 ? E8 ? ? ? ? 48 8B 38 48 C7 44 24 ? ? ? ? ? 48 8B 4B ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 8B 00 FF 15 ? ? ? ? 48 89 44 24 ? 48 8D 57 ? 48 8D 4C 24 ? E8 ? ? ? ? 48 8B 4C 24 ? 48 85 C9 74 ? 48 8B 01 48 8D 54 24 ? 48 3B CA 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 90 48 8B 4B ? 48 85 C9 74 ? 48 8B 01 48 3B CB 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 48 C7 43 ? ? ? ? ? 48 8B 8C 24 ? ? ? ? 48 33 CC E8 ? ? ? ? 48 8B 9C 24 ? ? ? ? 48 81 C4 ? ? ? ? 5F C3 CC CC CC CC CC CC CC 40 53 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 49 8B D8 88 54 24 ? 48 89 5C 24 ? 49 83 78 ? ? 74 ? 48 81 C1 ? ? ? ? 4C 8D 44 24 ? 48 8D 54 24 ? E8 ? ? ? ? 48 8B 08 48 83 C1 ? 48 8B D3 E8 ? ? ? ? 90 48 8B 4B ? 48 85 C9 74 ? 48 8B 01 48 3B CB 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 48 C7 43 ? ? ? ? ? 48 8B 4C 24 ? 48 33 CC E8 ? ? ? ? 48 83 C4 ? 5B C3 CC CC CC CC CC CC CC CC CC CC CC 40 53}
    MC void addValidSlotForContainerCallback(ContainerEnumName enumName, const std::function<bool(int)> callback);
    /// @signature {40 53 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 49 8B D8 88 54 24 ? 48 89 5C 24 ? 49 83 78 ? ? 74 ? 48 81 C1 ? ? ? ? 4C 8D 44 24 ? 48 8D 54 24 ? E8 ? ? ? ? 48 8B 08 48 83 C1 ? 48 8B D3 E8 ? ? ? ? 90 48 8B 4B ? 48 85 C9 74 ? 48 8B 01 48 3B CB 0F 95 C2 48 8B 40 ? FF 15 ? ? ? ? 48 C7 43 ? ? ? ? ? 48 8B 4C 24 ? 48 33 CC E8 ? ? ? ? 48 83 C4 ? 5B C3 CC CC CC CC CC CC CC CC CC CC CC 48 89 5C 24 ? 48 89 74 24}
    MC void addItemAllowedInContainerCallback(ContainerEnumName enumName, const std::function<bool(const ItemStackBase&)> callback);
};