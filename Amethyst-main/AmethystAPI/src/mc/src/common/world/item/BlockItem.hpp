/// @symbolgeneration
#pragma once
#include "amethyst/Imports.hpp"
#include "mc/src/common/world/item/Item.hpp"

/// @vptr {0x4E257C8}
class BlockItem : public Item {
public:
    /// @vidx {inherit}
    MC virtual ~BlockItem() override;

    /// @vidx {inherit}
    MC virtual bool isDestructive(int unk0) const override;

    /// @vidx {inherit}
    MC virtual bool isValidAuxValue(int unk0) const override;

    /// @vidx {inherit}
    MC virtual std::string buildDescriptionId(const ItemDescriptor& unk0, const CompoundTag* unk1) const override;

    /// @vidx {inherit}
    MC virtual ResolvedItemIconInfo getIconInfo(const ItemStackBase& unk0, int unk1, bool unk2) const override;

    /// @vidx {inherit}
    MC virtual Brightness getLightEmission(int unk0) const override;

    /// @vidx {inherit}
    MC virtual int getIconYOffset() const override;

    /// @vidx {inherit}
    MC virtual bool _calculatePlacePos(ItemStackBase& unk0, Actor& unk1, FacingID& unk2, BlockPos& unk3) const override;

    /// @vidx {inherit}
    MC virtual InteractionResult _useOn(ItemStack& unk0, Actor& unk1, BlockPos unk2, FacingID unk3, const Vec3& unk4) const override;

public:
    /// @signature {40 53 55 56 57 41 56 48 81 EC ? ? ? ? 49 8B F9 48 8B EA}
    MC BlockItem(const std::string& nameId, short mId, const HashedString& blockId);

    //BlockItem(const std::string& nameId, short mId);

    MC static uintptr_t $vtable_for_this;
};