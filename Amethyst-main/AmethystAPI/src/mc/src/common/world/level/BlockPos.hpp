#pragma once
#include <functional>
#include <mc/src-deps/core/math/Math.hpp>
#include <mc/src-deps/core/utility/BinaryStream.hpp>
#include <mc/src/common/world/Facing.hpp>
#include <mc/src/common/world/phys/Vec3.hpp>

class BlockPos {
public:
    int x;
    int y;
    int z;

    BlockPos() : x(0), y(0), z(0) {}

    BlockPos(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    BlockPos(const Vec3& vec)
    {
        this->x = static_cast<int>(std::floor(vec.x));
        this->y = static_cast<int>(std::floor(vec.y));
        this->z = static_cast<int>(std::floor(vec.z));
    }

	static const BlockPos ZERO;

    BlockPos below() const
    {
        return {this->x, this->y - 1, this->z};
    }

    BlockPos above() const
    {
        return {this->x, this->y + 1, this->z};
    }

    BlockPos north() const
    {
        return {this->x, this->y, this->z - 1};
    }

    BlockPos east() const
    {
        return {this->x + 1, this->y, this->z};
    }

    BlockPos south() const
    {
        return {this->x, this->y, this->z + 1};
    }

    BlockPos west() const
    {
        return {this->x - 1, this->y, this->z};
    }

    BlockPos neighbor(FacingID dir) const
    {
        switch (dir) {
            case FacingID::NORTH:
                return north();

            case FacingID::SOUTH:
                return south();

            case FacingID::WEST:
                return west();

            case FacingID::EAST:
                return east();

            case FacingID::UP:
                return above();

            case FacingID::DOWN:
                return below();

            default:
                std::unreachable();
        }
    }

	int distSqr(const BlockPos& other) const {
        int dx = x - other.x;
        int dy = y - other.y;
        int dz = z - other.z;
        return dx * dx + dy * dy + dz * dz;
    }

    constexpr size_t hashCode() const
    {
        // This implementation is completely guessed, please verify it for usage in actual game memory
        // only needed right now for mod memory, so impl hasn't been checked.
        size_t hash = 0;
        mce::Math::hash_accumulate(hash, x);
        mce::Math::hash_accumulate(hash, y);
        mce::Math::hash_accumulate(hash, z);
        return hash;
    }

	constexpr uint64_t asLong() const {
		// Bit layout: [X:26 | Z:26 | Y:12]
		return ((static_cast<uint64_t>(x) & 0x3FFFFFFULL) << 38)
			| ((static_cast<uint64_t>(z) & 0x3FFFFFFULL) << 12)
			| (static_cast<uint64_t>(y) & 0xFFFULL);
	}

	static BlockPos fromLong(uint64_t value) {
		int x = static_cast<int>(value >> 38);
		int y = static_cast<int>(value & 0xFFFULL);
		int z = static_cast<int>((value >> 12) & 0x3FFFFFFULL);

		// Correct for negatives (sign extension)
		if (x >= 0x2000000) x -= 0x4000000;
		if (y >= 0x800) y -= 0x1000;
		if (z >= 0x2000000) z -= 0x4000000;

		return BlockPos(x, y, z);
	}

	BlockPos operator+(const BlockPos& other) const {
		return BlockPos(x + other.x, y + other.y, z + other.z);
	}

	BlockPos operator-(const BlockPos& other) const {
		return BlockPos(x - other.x, y - other.y, z - other.z);
	}

    bool operator==(const BlockPos& other) const
    {
        return x == other.x && y == other.y && z == other.z;
    }

	static std::vector<BlockPos> betweenClosed(const BlockPos& a, const BlockPos& b) {
		std::vector<BlockPos> result;

		int minX = std::min(a.x, b.x);
		int maxX = std::max(a.x, b.x);
		int minY = std::min(a.y, b.y);
		int maxY = std::max(a.y, b.y);
		int minZ = std::min(a.z, b.z);
		int maxZ = std::max(a.z, b.z);

		for (int x = minX; x <= maxX; ++x)
			for (int y = minY; y <= maxY; ++y)
				for (int z = minZ; z <= maxZ; ++z)
					result.emplace_back(x, y, z);

		return result;
	}

    BlockPos(const BlockPos& other) : x(other.x), y(other.y), z(other.z) {}
};

// BinaryStream specialization
#include "mc/src-deps/core/utility/BinaryStream.hpp"

template <>
Bedrock::Result<BlockPos> ReadOnlyBinaryStream::get<BlockPos>();

template <>
void BinaryStream::write(BlockPos);

namespace std {
template <>
struct hash<BlockPos> {
    size_t operator()(const BlockPos& pos) const
    {
        return pos.hashCode();
    }
};
}

#include <format>

template <>
struct std::formatter<BlockPos> {
    constexpr auto parse(std::format_parse_context& ctx) {
        return ctx.begin(); // No format specifiers
    }

    template <typename FormatContext>
    auto format(const BlockPos& pos, FormatContext& ctx) const {
        return std::format_to(ctx.out(), "BlockPos(x: {}, y: {}, z: {})", pos.x, pos.y, pos.z);
    }
};