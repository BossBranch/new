#include "GuiData.hpp"
#include <amethyst/Memory.hpp>

void GuiData::_displayWhisperMessage(const std::string& a1, const std::string& a2, const std::string& a3, const std::string& a4)
{
    using function = decltype(&GuiData::_displayWhisperMessage);
    static function func = std::bit_cast<function>(SigScan("40 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4C 89 4D ? 4D 8B F0 4C 8B E2"));
    return (this->*func)(a1, a2, a3, a4);
}

void GuiData::displayLocalizableMessage(const std::string& a1, const std::vector<std::string>& a2)
{
    using function = decltype(&GuiData::displayLocalizableMessage);
    static function func = std::bit_cast<function>(SigScan("40 55 53 56 57 41 56 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 49 8B F8 48 8B DA 48 8B F1 0F 57 C0 0F 11 44 24"));
    return (this->*func)(a1, a2);
}
