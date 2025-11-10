#include "LevelSettings.hpp"


LevelSettings LevelSettings::$ctor(const LevelData& levelData, DimensionType dimType)
{
    alignas(LevelSettings) std::byte storage[sizeof(LevelSettings)];
    auto obj = reinterpret_cast<LevelSettings*>(&storage);

    using function = void(__fastcall*)(LevelSettings*, const LevelData&, DimensionType);
    static auto func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 41 8B D8"));
    func(obj, levelData, dimType);

    return std::move(*obj);
}

LevelSettings* LevelSettings::$ctorPtr(const LevelData& levelData, DimensionType dimType)
{
    void* mem = ::operator new(sizeof(LevelSettings));

    // call the game constructor in-place
    using function = void(__fastcall*)(LevelSettings*, const LevelData&, DimensionType);
    static auto func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 41 8B D8"));
    func(reinterpret_cast<LevelSettings*>(mem), levelData, dimType);

    return reinterpret_cast<LevelSettings*>(mem);
}
