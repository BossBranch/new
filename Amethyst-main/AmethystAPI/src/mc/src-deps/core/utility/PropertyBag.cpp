#include "PropertyBag.hpp"

PropertyBag::PropertyBag()
    : mJsonValue(Json::ValueType::nullValue), mChangeVersion(0) {}

PropertyBag::PropertyBag(const Json::Value& value) : mJsonValue(value), mChangeVersion(0)
{
}

PropertyBag::PropertyBag(const std::string& jsonString) 
    : mChangeVersion(0)
{
    Json::Reader reader;
    reader.parse(jsonString, mJsonValue);
}