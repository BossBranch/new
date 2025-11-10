#pragma once
#include <amethyst/Imports.hpp>
#include <json/json.h>

class PropertyBag {
public:
    Json::Value mJsonValue;
    int mChangeVersion;

    PropertyBag();
    PropertyBag(const Json::Value& value);
    PropertyBag(const std::string& jsonString);
    ~PropertyBag() = default;
};