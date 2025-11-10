#pragma once
#include <cstddef>

#include "mc/src-deps/core/string/StringHash.hpp"

namespace mce {
    class RenderMaterialGroupBase;
    class RenderMaterialInfo : public std::enable_shared_from_this<RenderMaterialInfo> {
    public:
        HashedString mHashedName;

        RenderMaterialInfo(const HashedString& name);
    };

    class MaterialPtr {
    public:
        std::shared_ptr<RenderMaterialInfo> mRenderMaterialInfoPtr;

        MaterialPtr() = default;
        MaterialPtr(mce::RenderMaterialGroupBase& materialGroup, const HashedString& materialName);

		bool isNull() const {
			return mRenderMaterialInfoPtr == nullptr;
		}
    };
}