/// @symbolgeneration
#pragma once
#include "mc/src/common/network/NetworkBlockPosition.hpp"
#include "mc/src/common/world/Facing.hpp"
#include "mc/src/common/world/inventory/transaction/ComplexInventoryTransaction.hpp"
#include "mc/src/common/world/level/block/Block.hpp"
#include "mc/src/common/world/phys/Vec3.hpp"

class Player;

enum class InventoryTransactionError : uint64_t {
    Unknown0 = 0,
    Success = 1,
    Unknown2 = 2,
    ProbablyError = 3,

    StateMismatch = 7
};

class ItemUseInventoryTransaction : public ComplexInventoryTransaction {
public:
    enum class ActionType {
        Place,
        Use,
        Destroy
    };

    ActionType mActionType;
    NetworkBlockPosition mPos;
    BlockRuntimeId mTargetBlockId;
    FacingID mFace;
    int32_t mSlot;
    NetworkItemStackDescriptor mItem;
    Vec3 mFromPos;
    Vec3 mClickPos;

public:
    ItemUseInventoryTransaction();

    void setTargetBlock(const Block& block)
    {
        this->mTargetBlockId = block.getRuntimeId();
    }

    /*void setSelectedItem(const ItemStack& stack)
    {
        NetworkItemStackDescriptor networkDescriptor(stack);
    }*/

    /// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 B4 24 ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 45 0F B6 E0}
    MC InventoryTransactionError handle(Player& player, bool isSenderAuthority);

    void resendPlayerState(Player& player) const {
        using function = decltype(&ItemUseInventoryTransaction::resendPlayerState);
        static auto func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B DA 48 8B 8A"));
        (this->*func)(player);
    }

    void resendBlocksAroundArea(Player& player, const BlockPos& pos, FacingID facing) const {
        using function = decltype(&ItemUseInventoryTransaction::resendBlocksAroundArea);
        static auto func = std::bit_cast<function>(SigScan("48 89 5C 24 ? 48 89 7C 24 ? 55 48 8B EC 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B CA"));
        (this->*func)(player, pos, facing);
    }
};

static_assert(sizeof(ItemUseInventoryTransaction) == 0x100);