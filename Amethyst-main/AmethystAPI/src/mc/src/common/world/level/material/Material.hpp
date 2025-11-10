/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>
#include "mc/src/common/world/level/material/MaterialType.hpp"

class Material {
public:
    MaterialType mType;
    bool mNeverBuildable;
    bool mAlwaysDestroyable;
    bool mLiquid;
    float mTranslucency;
    bool mBlocksMotion;
    bool mBlocksPrecipitation;
    bool mSolid;
    bool mSuperHot;

    bool isLiquid() const
    {
        return mLiquid;
    }

    /// @address {0x59EF9F8}
    MC static std::vector<std::unique_ptr<Material>> mMaterials;

    static Material& getMaterial(MaterialType type);
};