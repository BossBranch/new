/// @symbols
#pragma once
#include <amethyst/Imports.hpp>

#include "mc/src/common/world/level/block/ActorBlock.hpp"

/// @vptr {0x4E37018}
class ChestBlock : 
    public ActorBlock 
{
public: 
    MC static uintptr_t $vtable_for_this;

    enum class ChestType : int {
        Default = 0,
        Trapped = 1,
        Other = 2
    };
    
    ChestType mChestType;
    
    /** @signature {48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B 05 ? ? ? ? 48 8B D9 4C 8B 15} */
    MC ChestBlock(const std::string& nameId, short id, ChestType type, MaterialType materialType);

    /** @vidx {i} */ MC virtual ~ChestBlock() override;
    /** @vidx {i} */ MC virtual bool canProvideSupport(const Block& block, FacingID face, BlockSupportType type) const override;
    /** @vidx {i} */ MC virtual bool isContainerBlock() const override;
    /** @vidx {i} */ MC virtual bool isSignalSource() const override;
    /** @vidx {i} */ MC virtual bool shouldConnectToRedstone(BlockSource&, const BlockPos&, Direction::Type) const override;
    /** @vidx {i} */ MC virtual bool dispense(BlockSource& region, Container& container, int slot, const Vec3& pos, FacingID face) const override;
    /** @vidx {i} */ MC virtual void onMove(BlockSource& region, const BlockPos& from, const BlockPos& to) const override;
    /** @vidx {i} */ MC virtual bool detachesOnPistonMove(BlockSource&, BlockPos const&) const override;
    /** @vidx {i} */ MC virtual void setupRedstoneComponent(BlockSource& region, const BlockPos& pos) const override;
    /** @vidx {i} */ MC virtual bool breaksFallingBlocks(const Block& block, BaseGameVersion version) const override;
    /** @vidx {i} */ MC virtual bool getSecondPart(const IConstBlockSource&, const BlockPos&, BlockPos&) const override;
    /** @vidx {i} */ MC virtual bool hasComparatorSignal() const override;
    /** @vidx {i} */ MC virtual int getComparatorSignal(BlockSource& region, const BlockPos& pos, const Block& block, FacingID dir) const override;
    /** @vidx {i} */ MC virtual FacingID getMappedFace(FacingID face, const Block& block) const override;
    /** @vidx {i} */ MC virtual BlockLegacy& init() override;
    /** @vidx {i} */ MC virtual void onRemove(BlockSource& region, const BlockPos& pos) const override;
    /** @vidx {i} */ MC virtual void onPlace(BlockSource& region, const BlockPos& pos) const override;
    /** @vidx {i} */ MC virtual bool isInteractiveBlock() const override;
    /** @vidx {i} */ MC virtual bool use(Player& player, const BlockPos& pos, FacingID face) const override;
};



// 1.21.0.3
static_assert(sizeof(ChestBlock) == 992);