#pragma once
#include <memory>
#include <optional>
#include <map>
#include <mc/src-deps/coregraphics/TextureSetLayerTypes.hpp>
#include <mc/src-client/common/client/renderer/TexturePtr.hpp>
#include <mc/src-deps/core/utility/NonOwnerPointer.hpp>
#include <mc/src-deps/core/resource/ResourceHelper.hpp>
#include <mc/src-deps/minecraftrenderer/renderer/BedrockTexture.hpp>

namespace mce {
    class TextureGroupBase : public std::enable_shared_from_this<TextureGroupBase> {
    public:
        virtual ~TextureGroupBase();
        virtual mce::TexturePtr getTexture(const ResourceLocation& path, bool forceReload, std::optional<uint32_t> unk1, cg::TextureSetLayerType type);
    };
}