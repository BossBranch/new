/// @symbols
#pragma once
#include "mc/src/common/world/level/block/actor/BlockActor.hpp"
#include "mc/src/common/world/level/block/actor/RandomizableBlockActorContainers.hpp"
#include "mc/src/common/world/inventory/FillingContainer.hpp"

/// @vptr {0x4E6ED48, RandomizableBlockActorContainerBase}
/// @vptr {0x4E6EBD8, FillingContainer}
class ChestBlockActor : 
    public RandomizableBlockActorFillingContainer 
{
public:
    MC static uintptr_t $vtable_for_RandomizableBlockActorContainerBase; 
    MC static uintptr_t $vtable_for_FillingContainer;

    char mPadding624[768 - sizeof(RandomizableBlockActorFillingContainer)];

    /// @signature {48 89 5C 24 ? 48 89 4C 24 ? 57 48 83 EC ? 41 8B D9 48 8B F9 4C 8B 4C 24} */ 
    MC ChestBlockActor(BlockActorType type, std::string const& id, BlockActorRendererId rendererId, BlockPos const& pos, bool canBeDouble);

// const ChestBlockActor::`vftable'{for `RandomizableBlockActorContainerBase'}
    /** @vidx {i,  RandomizableBlockActorContainerBase} */ MC virtual ~ChestBlockActor() override;
    /** @vidx {i,  RandomizableBlockActorContainerBase} */ MC virtual void load(Level& unk0, const CompoundTag& unk1, DataLoadHelper& unk2) override;
    /** @vidx {i,  RandomizableBlockActorContainerBase} */ MC virtual bool save(CompoundTag& unk0) const override;
    /** @vidx {i,  RandomizableBlockActorContainerBase} */ MC virtual bool saveItemInstanceData(CompoundTag& unk0) const override;
    /** @vidx {i,  RandomizableBlockActorContainerBase} */ MC virtual void tick(BlockSource& unk0) override;
    /** @vidx {i,  RandomizableBlockActorContainerBase} */ MC virtual void onChanged(BlockSource& unk0) override;
    /** @vidx {i,  RandomizableBlockActorContainerBase} */ MC virtual void onPlace(BlockSource& unk0) override;
    /** @vidx {i,  RandomizableBlockActorContainerBase} */ MC virtual void onMove() override;
    /** @vidx {i,  RandomizableBlockActorContainerBase} */ MC virtual void onRemoved(BlockSource& unk0) override;
    /** @vidx {i,  RandomizableBlockActorContainerBase} */ MC virtual void triggerEvent(int unk0, int unk1) override;
    /** @vidx {i,  RandomizableBlockActorContainerBase} */ MC virtual void clearCache() override;
    /** @vidx {i,  RandomizableBlockActorContainerBase} */ MC virtual void onNeighborChanged(BlockSource& unk0, const BlockPos& unk1) override;
    /** @vidx {i,  RandomizableBlockActorContainerBase} */ MC virtual BlockActor* getCrackEntity(BlockSource& unk0, const BlockPos& unk1) override;
    /** @vidx {i,  RandomizableBlockActorContainerBase} */ MC virtual void getDebugText(std::vector<std::string>& unk0, const BlockPos& unk1) override;
    /** @vidx {i,  RandomizableBlockActorContainerBase} */ MC virtual std::string getName() const override;
    /** @vidx {i,  RandomizableBlockActorContainerBase} */ MC virtual Container* getContainer() override;
    /** @vidx {i,  RandomizableBlockActorContainerBase} */ MC virtual const Container* getContainer() const override;
    /** @vidx {i,  RandomizableBlockActorContainerBase} */ MC virtual std::unique_ptr<BlockActorDataPacket> _getUpdatePacket(BlockSource& unk0) override;
    /** @vidx {i,  RandomizableBlockActorContainerBase} */ MC virtual void _onUpdatePacket(const CompoundTag& unk0, BlockSource& unk1) override;
    /** @vidx {43, RandomizableBlockActorContainerBase} */ MC virtual void loadItems(const CompoundTag& unk0, Level& unk1);
    /** @vidx {44, RandomizableBlockActorContainerBase} */ MC virtual bool saveItems(CompoundTag& unk0) const;
    /** @vidx {45, RandomizableBlockActorContainerBase} */ MC virtual void openBy(Player& unk0);
    /** @vidx {46, RandomizableBlockActorContainerBase} */ MC virtual void playOpenSound(BlockSource& unk0);
    /** @vidx {47, RandomizableBlockActorContainerBase} */ MC virtual void playCloseSound(BlockSource& unk0);
    /** @vidx {48, RandomizableBlockActorContainerBase} */ MC virtual bool _canOpenThis(BlockSource& unk0) const;
    /** @vidx {49, RandomizableBlockActorContainerBase} */ MC virtual AABB getObstructionAABB() const;
    /** @vidx {50, RandomizableBlockActorContainerBase} */ MC virtual bool _detectEntityObstruction(BlockSource& unk0) const;

// const ChestBlockActor::`vftable'{for `FillingContainer'}
    /** @vidx {i, FillingContainer} */ MC virtual void serverInitItemStackIds(int, int, std::function<void(int, const ItemStack&)>) override;
    /** @vidx {i, FillingContainer} */ MC virtual void addContentChangeListener(ContainerContentChangeListener*) override;
    /** @vidx {i, FillingContainer} */ MC virtual void removeContentChangeListener(ContainerContentChangeListener*) override;
    /** @vidx {i, FillingContainer} */ MC virtual const ItemStack& getItem(int) const override;
    /** @vidx {i, FillingContainer} */ MC virtual void setItem(int, const ItemStack&) override;
    /** @vidx {i, FillingContainer} */ MC virtual void setItemWithForceBalance(int, const ItemStack&, bool) override;
    /** @vidx {i, FillingContainer} */ MC virtual int getContainerSize() const override;
    /** @vidx {i, FillingContainer} */ MC virtual int getMaxStackSize() const override;
    /** @vidx {i, FillingContainer} */ MC virtual void startOpen(Player&) override;
    /** @vidx {i, FillingContainer} */ MC virtual void stopOpen(Player&) override;
    /** @vidx {i, FillingContainer} */ MC virtual void setContainerChanged(int) override;
    /** @vidx {i, FillingContainer} */ MC virtual void initializeContainerContents(BlockSource&) override;
    /** @vidx {i, FillingContainer} */ MC virtual void clearSlot(int slot) override;
    /** @vidx {i, FillingContainer} */ MC virtual void clearInventory(int size) override;
};

static_assert(sizeof(ChestBlockActor) == 768);