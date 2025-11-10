#include "mc/src-client/common/client/renderer/block/BlockGraphics.hpp"
#include <amethyst/Memory.hpp>

void BlockGraphics::setTextureItem(const std::string& allFaces) 
{
    setTextureItem(allFaces, allFaces, allFaces, allFaces, allFaces, allFaces);
}