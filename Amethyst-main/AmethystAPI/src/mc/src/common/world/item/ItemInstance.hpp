/// @symbols
#pragma once
#include "mc/src/common/world/item/ItemStackBase.hpp"

class ItemStackBase;

/** @vptr {0x4E2B678} */
class ItemInstance : public ItemStackBase {
public:
    /** @sig {40 53 48 83 EC ? 0F 28 02 48 8B D9 48 8B 44 24 ? 48 8D 54 24 ? 66 0F 7F 44 24 ? 48 89 44 24 ? E8 ? ? ? ? 48 8D 05 ? ? ? ? 48 89 03 48 8B C3 48 83 C4} */
    MC ItemInstance(const std::string& name, int count, int aux, const CompoundTag* data = nullptr);
    ItemInstance(const ItemStackBase& base) : 
        ItemStackBase(base) {}

    /** @vidx {i} */ MC virtual ~ItemInstance() override;
    /** @vidx {i} */ MC virtual void reinit(const Item& item, int count, int auxValue) override;
    /** @vidx {i} */ MC virtual void reinit(const BlockLegacy& block, int count) override;
    /** @vidx {i} */ MC virtual void reinit(std::string_view name, int count, int auxValue) override;
};

