#pragma once
#include "Json.hpp"
#include "amethyst/Log.hpp"
#include <string>
#include <vector>
#include <unordered_set>
using json = nlohmann::json;

class Config {
public:
    std::string injectedMod;
    std::string gameVersion;
    std::unordered_set<std::string> mods;
    bool promptDebugger;

public:
    Config() = default;
    Config(std::string& text);
};