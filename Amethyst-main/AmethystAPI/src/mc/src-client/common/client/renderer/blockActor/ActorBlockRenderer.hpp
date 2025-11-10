/// @symbols
#include <amethyst/Imports.hpp>

class BaseActorRenderContext;
class BlockSource;
class Block;
namespace dragon {
    class RenderMetadata;
}

class ActorBlockRenderer {
public:
    
    MC void render(BaseActorRenderContext& ctx, const dragon::RenderMetadata& metadata, BlockSource& src, const Block* block, float unk);
};