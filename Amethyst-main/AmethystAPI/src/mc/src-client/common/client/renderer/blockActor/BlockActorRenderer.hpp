/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>

#include <mc/src-client/common/client/renderer/BaseActorRenderer.hpp>
#include <mc/src-client/common/client/renderer/BaseActorRenderContext.hpp>
#include <mc/src/common/world/phys/Vec3.hpp>

struct BlockActorRenderData;
class NameTagRenderObject;
class Tessellator;
class BlockActor;
class BlockSource;
class Block;

class BlockActorRenderer : public BaseActorRenderer {
public:
    BlockActorRenderer() : BaseActorRenderer() {};

    virtual ~BlockActorRenderer() override = default;
    virtual void render(BaseActorRenderContext&, BlockActorRenderData&) = 0;
    virtual void renderAlpha(BaseActorRenderContext&, BlockActorRenderData&) {};

    /// @signature {40 53 48 83 EC ? 48 8B DA 45 33 D2}
    MC virtual std::vector<NameTagRenderObject> extractText(Tessellator&, BlockActor&, const std::string&, std::vector<int>&, Vec3, bool);
};

struct BlockActorRenderData {
    /* this + 0  */ BlockSource& renderSource;
    /* this + 8  */ BlockActor& entity;
    /* this + 16 */ const Block& block;
    /* this + 24 */ const Vec3& position;
};