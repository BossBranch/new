#pragma once
#include <mc/src-deps/core/string/StringHash.hpp>
#include <mc/src/common/AppPlatformListener.hpp>

namespace mce {
class RenderMaterialInfo;
class RenderMaterialGroupBase {
    public:
        virtual ~RenderMaterialGroupBase();
        virtual std::shared_ptr<RenderMaterialInfo>& getMaterialInfo(const HashedString& material);
        virtual void clearMaterial(const HashedString& material);
    };
};