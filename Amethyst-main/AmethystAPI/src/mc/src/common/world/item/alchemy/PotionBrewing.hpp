/// @symbolgeneration
#pragma once
#include "amethyst/Imports.hpp"
#include <vector>
#include "mc/src/common/world/item/ItemDescriptor.hpp"

class PotionBrewing {
public:
    class Ingredient {
    public:
        int mItemId;
        int mData;
    };

    template<typename T>
    class Mix {
    public:
        T mFrom;
        PotionBrewing::Ingredient mIngredient;
        T mTo;
    };

    /// @address {0x59DA918}
    MC static std::vector<PotionBrewing::Mix<ItemDescriptor>> mPotionMixes;

    /// @address {0x59DA978}
    MC static std::vector<PotionBrewing::Mix<const Item&>> mContainerMixes;
};