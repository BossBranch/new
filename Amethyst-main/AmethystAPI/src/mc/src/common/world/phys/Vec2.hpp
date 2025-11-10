#pragma once
#include <format>

class Vec2 {
public:
    float x;
    float y;

    Vec2() : x(0), y(0) {}
    Vec2(float x, float y) : x(x), y(y) {}  
};

template <>
struct std::formatter<Vec2> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin(); 
    }

    template <typename FormatContext>
    auto format(const Vec2& pos, FormatContext& ctx) const {
        return std::format_to(ctx.out(), "Vec2(x: {}, y: {})", pos.x, pos.y);
    }
};