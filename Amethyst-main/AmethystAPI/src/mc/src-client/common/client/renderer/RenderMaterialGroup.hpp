/// @symbols
#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src/common/AppPlatformListener.hpp>
#include <mc/src-deps/renderer/RenderMaterialGroupBase.hpp>
#include "mc/src-deps/minecraftrenderer/renderer/MaterialPtr.hpp"

namespace mce {
    class RenderMaterialInfo;
    class RenderMaterialGroup : public mce::RenderMaterialGroupBase, public AppPlatformListener {
    public:
		/// @address {0x59C02F0}
        MC static RenderMaterialGroup common;

		/// @address {0x59C0450}
        MC static RenderMaterialGroup switchable;

        mce::MaterialPtr getMaterial(const HashedString& name) {
            return mce::MaterialPtr::MaterialPtr(*this, name);
        }
    };
};