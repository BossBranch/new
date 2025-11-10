/// @symbolgeneration
#pragma once
#include "amethyst/Imports.hpp"
#include "mc/src/common/network/packet/Packet.hpp"
#include "mc/src/common/ActorUniqueID.hpp"
#include "mc/src/common/world/level/BlockPos.hpp"

enum class ContainerID : unsigned char;
enum class ContainerType : signed char;
struct ActorUniqueID;

/// @vptr {0x4CFE920}
class ContainerOpenPacket :
	public Packet 
{
public:
    ContainerID mContainerId;
    ContainerType mType;
    BlockPos mPos; // <- actually NetworkBlockPosition
    ActorUniqueID mEntityUniqueID;

    ContainerOpenPacket(ContainerID id, ContainerType type, const BlockPos& pos, const ActorUniqueID& uniqueId) :
        mContainerId(id),
        mType(type),
        mPos(pos),
        mEntityUniqueID(uniqueId)
    {
    }

    /// @vidx {0}
    MC virtual ~ContainerOpenPacket() override;
    
    /// @vidx {1}
    MC virtual MinecraftPacketIds getId() const override;

    /// @vidx {2}
    MC virtual std::string getName() const override;
    
    /// @vidx {4}
    MC virtual void write(BinaryStream& out) const override;

    /// @vidx {8}
    MC virtual Bedrock::Result<void, std::error_code> _read(ReadOnlyBinaryStream& in) override;
};