#pragma once 
#include <optional>
#include <mc/src-deps/core/math/DividedPos2d.h>

class IPreliminarySurfaceProvider {
public:
    virtual ~IPreliminarySurfaceProvider() = default;
    virtual std::optional<short> getPreliminarySurfaceLevel(QuartPos2d worldQuartPos) const = 0;
};