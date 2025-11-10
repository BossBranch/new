#pragma once
#include <format>
class BlockPos;
class Vec3;

namespace Facing {
    enum class Name : unsigned char {
        DOWN,
        UP,
        NORTH,
        SOUTH,
        WEST,
        EAST,
        MAX
    };

	const Facing::Name DIRECTIONS[6] = {
		Facing::Name::DOWN,
		Facing::Name::UP,
		Facing::Name::NORTH,
		Facing::Name::SOUTH,
		Facing::Name::WEST,
		Facing::Name::EAST
	};

	class BlockPos getOffset(Facing::Name face);
	Vec3 normal(Facing::Name face);

	enum class Axis : int {
		X = 0,
		Y = 1,
		Z = 2,
		Count = 3
	};

	const Axis AXES[3] = {
		Axis::X,
		Axis::Y,
		Axis::Z
	};

	inline int choose(Axis axis, int x, int y, int z) {
		switch (axis) {
			case Axis::X: return x;
			case Axis::Y: return y;
			case Axis::Z: return z;
			default: std::unreachable();
		}
	}

    Facing::Name getOpposite(Facing::Name face);
    Facing::Name getClockWise(Facing::Name face);
    Facing::Name getCounterClockWise(Facing::Name face);
    float getYAngle(Facing::Name face);
	float getXAngle(Facing::Name face);

	// Axis direction is technically not actually a type in mc, but seemed useful enough to have
	enum class AxisDirection : int {
        POSITIVE = 1,
        NEGATIVE = -1
    };

	inline AxisDirection getAxisDirection(Name face) {
        switch (face) {
            case Name::DOWN:  return AxisDirection::NEGATIVE;
            case Name::UP:    return AxisDirection::POSITIVE;
            case Name::NORTH: return AxisDirection::NEGATIVE;
            case Name::SOUTH: return AxisDirection::POSITIVE;
            case Name::WEST:  return AxisDirection::NEGATIVE;
            case Name::EAST:  return AxisDirection::POSITIVE;
            default: std::unreachable();
        }
    }

	inline Axis getAxis(Name face) {
        switch (face) {
            case Name::DOWN:  return Axis::Y;
            case Name::UP:    return Axis::Y;
            case Name::NORTH: return Axis::Z;
            case Name::SOUTH: return Axis::Z;
            case Name::WEST:  return Axis::X;
            case Name::EAST:  return Axis::X;
            default: std::unreachable();
        }
    }

	Name getNearest(const Vec3& vec);

	inline Name fromDirectionAndAxis(AxisDirection direction, Axis axis) {
		switch (axis) {
			case Axis::X:
				return direction == AxisDirection::POSITIVE ? Name::EAST : Name::WEST;
			case Axis::Y:
				return direction == AxisDirection::POSITIVE ? Name::UP : Name::DOWN;
			case Axis::Z:
				return direction == AxisDirection::POSITIVE ? Name::SOUTH : Name::NORTH;
			default:
				std::unreachable();
		}
	}
};

typedef Facing::Name FacingID;


template <>
struct std::formatter<FacingID> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin(); // No custom specifiers
    }

    template <typename FormatContext>
    auto format(const FacingID& face, FormatContext& ctx) const {
        std::string_view name;
        switch (face) {
            case FacingID::DOWN:  name = "down";  break;
            case FacingID::UP:    name = "up";    break;
            case FacingID::NORTH: name = "north"; break;
            case FacingID::SOUTH: name = "south"; break;
            case FacingID::WEST:  name = "west";  break;
            case FacingID::EAST:  name = "east";  break;
            default:              name = "unknown"; break;
        }
        return std::format_to(ctx.out(), "{}", name);
    }
};