/// @symbolgeneration
#pragma once
#include "amethyst/Imports.hpp"
#include "mc/src/common/network/packet/Packet.hpp"
#include "mc/src/common/world/containers/FullContainerName.hpp"
#include "mc/src/common/world/inventory/network/NetworkItemStackDescriptor.hpp"

enum class ContainerID : uint8_t;
class Player;
class ItemStack;

/// @vptr {0x4D78778}
class InventoryContentPacket
    : public Packet
{
public:
    ContainerID mInventoryId;
    std::vector<NetworkItemStackDescriptor> mSlots;

    /// @signature {48 89 5C 24 ? 48 89 6C 24 ? 48 89 4C 24 ? 56 57 41 56 48 81 EC ? ? ? ? 49 8B F0 4C 8B F1}
    MC InventoryContentPacket(ContainerID id, const std::vector<ItemStack>& items);

    /// @vidx {0}
    MC virtual ~InventoryContentPacket() override;
    /// @vidx {1}
    MC virtual MinecraftPacketIds getId() const override;
    /// @vidx {2}
    MC virtual std::string getName() const override;
    /// @vidx {4}
    MC virtual void write(BinaryStream& out) const override;
    /// @vidx {8}
    MC virtual Bedrock::Result<void, std::error_code> _read(ReadOnlyBinaryStream& in) override;

// Non-virtuals
public:
    /// @signature {48 89 5C 24 ? 55 56 57 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 4D 8B F0 0F B6 FA}
    MC static InventoryContentPacket fromPlayerInventoryId(ContainerID id, Player& player);
};

static_assert(sizeof(InventoryContentPacket) == 0x50);