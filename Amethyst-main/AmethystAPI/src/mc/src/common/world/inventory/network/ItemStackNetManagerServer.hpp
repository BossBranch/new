/// @symbolgeneration
#pragma once
#include <vector>
#include "amethyst/Imports.hpp"

class ItemStackResponseInfo;
class ItemStackRequestData;

class ItemStackNetManagerServer {
public:
    /// @signature {48 89 5C 24 ? 55 56 57 41 56 41 57 48 83 EC ? 49 8B F8 48 8B F2 48 8B E9}
    MC void _handleRequestData(std::vector<ItemStackResponseInfo>& info, const ItemStackRequestData* data);
};