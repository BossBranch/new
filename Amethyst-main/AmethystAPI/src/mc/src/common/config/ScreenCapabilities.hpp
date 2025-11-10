#pragma once
#include <cstdint>
#include "mc/src-deps/core/utility/AutomaticID.hpp"

class IScreenCapabilities {
public:
    virtual ~IScreenCapabilities() = 0;
    virtual bool isOfType(AutomaticID<IScreenCapabilities, uint16_t> id) = 0;
};