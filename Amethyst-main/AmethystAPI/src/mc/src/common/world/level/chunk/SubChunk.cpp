#include "SubChunk.hpp"
#include <amethyst/Memory.hpp>

void SubChunk::serialize(IDataOutput& steam, bool network) const
{
    using function = decltype(&SubChunk::serialize);
    static auto func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 48 89 6C 24 ? 56 57 41 54 41 56 41 57 48 81 EC ? ? ? ? 41 0F B6 E8"));
    (this->*func)(steam, network);
}

void SubChunk::deserialize(IDataInput& steam, const BlockPalette& pallette, const SubChunkPos& pos, std::optional<DeserializationChanges*> changes)
{
    using function = decltype(&SubChunk::deserialize);
    static auto func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 4C 89 4C 24 ? 49 8B F8 48 8B DA"));
    (this->*func)(steam, pallette, pos, changes);
}
