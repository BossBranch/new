#pragma once
#include <cstdint>
#include <format>
#include <mc/src/common/world/level/BlockPos.hpp>
#include <mc/src/common/world/level/ChunkPos.hpp>

class ChunkPos {
public:
    union {
        struct {
        public:
            int32_t x;
            int32_t z;
        };

    public:
        int64_t packed;
    };

public:
    ChunkPos() {
        x = 0;
        z = 0;
    };

    ChunkPos(int32_t x, int32_t z) {
        this->x = x;
        this->z = z;
    }

    ChunkPos(int64_t packed) {
        this->packed = packed;
    }

    ChunkPos(const BlockPos& pos) {
        x = pos.x / 16;
        z = pos.z / 16;
    }
};

template <>
struct std::formatter<ChunkPos> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin(); // No custom format specifiers
    }

    template <typename FormatContext>
    auto format(const ChunkPos& pos, FormatContext& ctx) const {
        return std::format_to(ctx.out(), "ChunkPos(x: {}, z: {})", pos.x, pos.z);
    }
};