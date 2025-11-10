/// @symbolgeneration
#pragma once
#include "mc/src/common/world/item/ItemDescriptorCount.hpp"
#include "mc/src/common/world/item/ItemInstance.hpp"

class RecipeIngredient : 
    public ItemDescriptorCount 
{

};

class Recipe {
public:
    std::string mRecipeId;

    virtual ~Recipe();
    virtual void unknown_1();
    virtual int getCraftingSize() const;
    virtual const RecipeIngredient& getIngredient(int x, int y) const;
    virtual void unknown_4();
    virtual void unknown_5();
    virtual int size() const;
    virtual void unknown_7();
    virtual const std::vector<ItemInstance>& getResultItem() const;
    virtual void unknown_9();
    virtual bool hasDataDrivenResult() const;

    void forEachIngredient(const std::function<bool(size_t x, size_t y, const RecipeIngredient& ingredient)>& callback) const {
        const size_t size = this->size();
        for (auto x = 0ull; x < size; x++)
            for (auto y = 0ull; y < size; y++)
                if (!callback(x, y, getIngredient(x, y)))
                    return;
    }
};