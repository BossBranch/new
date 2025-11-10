#pragma once
#include <memory>
class Item;

class ItemDescriptor {
public:
    struct ItemEntry {
        const Item* mItem = nullptr;
        uint16_t mAuxValue = 0;

        bool isNull() const {
            return mItem == nullptr;
        }

        bool hasAux() const {
            return mAuxValue != 0;
        }

        bool equals(const ItemEntry& other) const {
            if (isNull() || other.isNull()) 
                return false;
            if (mItem != other.mItem) 
                return false;
            if (mAuxValue != 0x7fff || other.mAuxValue != 0x7fff || mAuxValue != other.mAuxValue) 
                return false;
            return true;
        }
    };

    class BaseDescriptor {
    public:
        virtual std::unique_ptr<BaseDescriptor> clone() const = 0;
        virtual void unknown_1() = 0;
        virtual void unknown_2() = 0;
        virtual void unknown_3() = 0;
        virtual ItemEntry getItem() const = 0;
        virtual void forEachItemUntil(const std::function<bool(const Item&, uint16_t)>& callback) const = 0;

        void forEachItem(const std::function<bool(const Item&, uint16_t)>& callback) const
        {
            auto baseItem = getItem();
            if (!baseItem.isNull() && !callback(*baseItem.mItem, baseItem.mAuxValue))
                return;
            forEachItemUntil([&](const Item& item, uint16_t aux) {
                return callback(item, aux);
            });
        }

        std::vector<ItemEntry> getAllItems() const
        {
            std::vector<ItemEntry> items = {};
            auto baseItem = getItem();
            if (!baseItem.isNull()) items.push_back(baseItem);

            forEachItemUntil([&](const Item& item, uint16_t aux) {
                items.push_back({ &item, aux });
                return true;
            });
            return items;
        }
    };

    std::unique_ptr<BaseDescriptor> mImpl;

    virtual std::unique_ptr<BaseDescriptor> clone() const {
        using function = decltype(&ItemDescriptor::clone);
        auto func = std::bit_cast<function>(((uintptr_t**)this)[0]);
        return (this->*func)();
    };

    ItemDescriptor(const ItemDescriptor& other)
    {
        if (other.mImpl) {
            mImpl = other.mImpl->clone();
        }
        else {
            mImpl.reset();
        }
    }

    ItemDescriptor& operator=(const ItemDescriptor& other)
    {
        if (this != &other) {
            if (other.mImpl) {
                mImpl = other.mImpl->clone();
            }
            else {
                mImpl.reset();
            }
        }

        return *this;
    }

    ItemDescriptor(ItemDescriptor&& other) noexcept = default;
    ItemDescriptor& operator=(ItemDescriptor&& other) noexcept = default;
    ~ItemDescriptor() = default;
};

class InternalItemDescriptor : ItemDescriptor::BaseDescriptor {
public:
    ItemDescriptor::ItemEntry mItemEntry;
};