#pragma once
#include <cstdint>

enum class Difficulty : int32_t {
    Peaceful = 0x0000,
    Easy = 0x0001,
    Normal = 0x0002,
    Hard = 0x0003,
    Count = 0x0004,
    Unknown = 0x0005,
};