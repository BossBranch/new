/// @symbolgeneration
#include <amethyst/Imports.hpp>

#include <mc/src-client/common/client/renderer/TexturePtr.hpp>
#include <mc/src-client/common/client/renderer/TextureGroup.hpp>
#include <mc/src-client/common/client/renderer/blockActor/BlockActorRenderer.hpp>
#include <mc/src-deps/core/resource/ResourceHelper.hpp>

class ActorTextureInfo {
public:
    std::byte padding0[320];
    /*std::byte padding[0x10];
    mce::TexturePtr mClientTexture;
    mce::TexturePtr unk1;
    std::byte padding2[0x8];
    mce::TexturePtr unk2;
    std::byte padding3[0x70];
    ResourceLocation unk3;
    std::byte padding4[0x20];*/
};

class TextureJSONParser {
public:
    /// @signature {48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B C8}
    MC static ActorTextureInfo getTextureInfoFromTextureSet(const std::shared_ptr<mce::TextureGroup>& textureGroup, const Json::Value& value);
};

class ChestModel {
    std::byte padding[0xB80];
};

/// @vptr {0x4D5DC78}
class ChestRenderer : 
    public BlockActorRenderer
{
public:
    ActorTextureInfo largeTex;
    ActorTextureInfo normalTex;
    ActorTextureInfo trappedLargeTex;
    ActorTextureInfo trappedTex;
    ActorTextureInfo enderTex;
    ChestModel mChestModel;
    ChestModel mLargeChestModel;

    /// @signature {48 89 54 24 ? 48 89 4C 24 ? 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24}
    MC static void $constructor(ChestRenderer* self, const std::shared_ptr<mce::TextureGroup>& textureGroup);

    /// @signature {48 89 54 24 ? 48 89 4C 24 ? 55 53 56 57 41 54 41 55 41 56 41 57 48 8D AC 24}
    MC ChestRenderer(const std::shared_ptr<mce::TextureGroup>& textureGroup);

    /// @vidx {0}
    MC virtual ~ChestRenderer() override;

    /// @vidx {2}
    MC virtual void render(BaseActorRenderContext&, BlockActorRenderData&) override;
};

static_assert(sizeof(ChestRenderer) == 7608);
static_assert(offsetof(ChestRenderer, normalTex) == 440);