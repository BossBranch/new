#include "LevelData.hpp"
#include <mc/src-deps/core/utility/StringUtils.hpp>

LevelData LevelData::$ctor(bool useEducationEditionFeatures)
{
    alignas(LevelData) std::byte storage[sizeof(LevelData)];
    auto obj = reinterpret_cast<LevelData*>(&storage);

    using function = void(__fastcall*)(LevelData*, bool);
    static auto func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 44 0F B6 F2 48 8B F1 48 89 4D"));
    func(obj, useEducationEditionFeatures);

    return std::move(*obj);
}

GameType LevelData::getGameType() const
{
    auto it = mOverrides.find("gameType");
    if (it != mOverrides.end())
    {
        if (std::holds_alternative<GameType>(it->second.mValue))
        {
            return std::get<GameType>(it->second.mValue);
        }
    }

    auto it2 = mValues.find("gameType");
    if (it2 != mValues.end())
    {
        if (std::holds_alternative<GameType>(it2->second.mValue))
        {
            return std::get<GameType>(it2->second.mValue);
        }
    }

    return GameType::Default;
}

LevelSeed64 LevelData::getSeed() const
{
    auto it = mOverrides.find("seed");
    if (it != mOverrides.end()) {
        if (std::holds_alternative<LevelSeed64>(it->second.mValue)) {
            return std::get<LevelSeed64>(it->second.mValue);
        }
    }

    auto it2 = mValues.find("seed");
    if (it2 != mValues.end()) {
        if (std::holds_alternative<LevelSeed64>(it2->second.mValue)) {
            return std::get<LevelSeed64>(it2->second.mValue);
        }
    }

    return LevelSeed64(0);
}

const std::string& LevelData::getEducationOid() const
{
    auto it = mOverrides.find("educationOid");
    if (it != mOverrides.end()) {
        if (std::holds_alternative<std::string>(it->second.mValue)) {
            return std::get<std::string>(it->second.mValue);
        }
    }

    auto it2 = mValues.find("educationOid");
    if (it2 != mValues.end()) {
        if (std::holds_alternative<std::string>(it2->second.mValue)) {
            return std::get<std::string>(it2->second.mValue);
        }
    }

    return Util::EmptyString;
}
