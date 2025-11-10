/// @symbols
#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src/common/network/packet/Packet.hpp>
#include <mc/src/common/nbt/CompoundTagVariant.hpp>
#include <mc/src/common/nbt/CompoundTag.hpp>
#include <mc/src/common/network/NetworkBlockPosition.hpp>

/// @vptr {0x4D77D38}
class BlockActorDataPacket : public Packet {
public:
    NetworkBlockPosition mPos;
    CompoundTag mData;

	BlockActorDataPacket() 
		: mPos(), mData() {}

	BlockActorDataPacket(const BlockPos& pos, CompoundTag&& tag)
		: mPos(pos), mData(std::move(tag)) {}

    /// @vidx {i}
    MC virtual ~BlockActorDataPacket() override;

	/// @vidx {i}
	MC virtual MinecraftPacketIds getId() const override;

	/// @vidx {i}
	MC virtual std::string getName() const override;

	/// @vidx {i}
	MC virtual void write(BinaryStream& unk0) const override;

	/// @vidx {i}
	MC virtual Bedrock::Result<void, std::error_code> _read(ReadOnlyBinaryStream& unk0) override;
};