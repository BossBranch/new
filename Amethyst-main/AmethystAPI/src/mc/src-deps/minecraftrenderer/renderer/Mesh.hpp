/// @symbols
#pragma once
#include <amethyst/Imports.hpp>
#include <mc/src-client/common/client/renderer/TexturePtr.hpp>
#include <mc/src-deps/minecraftrenderer/renderer/BedrockTexture.hpp>
#include <mc/src-deps/minecraftrenderer/renderer/MeshData.hpp>

namespace mce {
    class ClientTexture;
    class ServerTexture;
    class TexturePtr;
    class MeshContext;
    class MaterialPtr;

    class Mesh {
    public:
        /* this + 0   */ std::byte padding0[120];
        /* this + 120 */ mce::MeshData mMeshData;
        /* this + 392 */ std::byte padding392[536 - 392];

    public:
		/// @sig {48 89 5C 24 ? 48 89 74 24 ? 57 48 81 EC ? ? ? ? 49 8B D8 C6 44 24}
        MC void renderMesh(mce::MeshContext& meshContext, const mce::MaterialPtr& materialPtr) const;

		/// @sig {40 53 56 57 48 81 EC ? ? ? ? 48 8B D9 C6 44 24}
        MC void renderMesh(mce::MeshContext& meshContext, const mce::MaterialPtr& materialPtr, const std::variant<std::monostate, mce::TexturePtr, mce::ClientTexture, mce::ServerTexture>& texture) const;
    };

    static_assert(sizeof(Mesh) == 536);
}

