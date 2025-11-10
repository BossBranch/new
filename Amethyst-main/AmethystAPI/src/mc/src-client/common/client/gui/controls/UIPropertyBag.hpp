/// @symbols
#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src-deps/core/utility/PropertyBag.hpp>

class UIControl;

class UIPropertyBag : public PropertyBag {
public:
    class ContextObject {
    public:
        int32_t mCount;
    };

    class PropertyChangedNotificationInfo {
    public:
        std::string mTargetPropertyName;
        std::weak_ptr<UIControl> mTargetControl;
        std::function<void(const std::weak_ptr<UIControl>&, std::string_view, const Json::Value&, UIPropertyBag::ContextObject)> mCallback;
    };

    std::map<std::string, std::vector<UIPropertyBag::PropertyChangedNotificationInfo>> mPropertyChangedNotificationInfoMap;

public:
    UIPropertyBag();
    UIPropertyBag(const Json::Value& value);

    virtual ~UIPropertyBag() = default;

    /*
     * Using the template without specialization will cause error.
     */
    template<typename T>
    void set(std::string_view name, const T& value) {
        static_assert(sizeof(T) == 0, "UIPropertyBag::set<T> is not imported for type T.");
    }

    /** @sig {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8B EC 48 83 EC ? 4D 8B F8 48 89 55} */
    template <>
    MC void set<std::string>(std::string_view name, const std::string& value);

    /** @sig {48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 49 8B F0 48 8B EA 48 8B F9 FF 41} */
    template<>
    MC void set<bool>(std::string_view name, const bool& value);

    /** @sig {48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 48 83 EC ? 0F 29 74 24 ? 49 8B F0} */
    template<>
    MC void set<float>(std::string_view name, const float& value);
};