#pragma once
#include <cstdint>

enum class Rotation : uint8_t {
    None               = 0,
    Rotate90           = 1 << 0,
    Clockwise90        = 1 << 0,
    Rotate180          = 1 << 1,
    Clockwise180       = 1 << 1,
    Total              = 1 << 2,
    CounterClockwise90 = Clockwise90 | Clockwise180,
    Rotate270          = Clockwise90 | Clockwise180,
};