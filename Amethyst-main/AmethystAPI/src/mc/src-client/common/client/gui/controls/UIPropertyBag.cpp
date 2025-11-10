#include "UIPropertyBag.hpp"

UIPropertyBag::UIPropertyBag() : PropertyBag() {}

UIPropertyBag::UIPropertyBag(const Json::Value& value)
    : PropertyBag(value) {}
