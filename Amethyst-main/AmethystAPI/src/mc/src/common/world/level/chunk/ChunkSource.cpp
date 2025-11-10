#include <mc/src/common/world/level/chunk/ChunkSource.hpp>
#include <amethyst/Memory.hpp>
#include <mc/src/common/world/level/dimension/Dimension.hpp>

ChunkSource::ChunkSource(Dimension* dimension, int side) : Bedrock::EnableNonOwnerReferences()
{
    this->mChunkSide = side;

    if (dimension) {
        this->mLevel = &dimension->getLevel();
        this->mLevelChunkBuilderData = dimension->mLevelChunkBuilderData.get();
    }
    else {
        this->mLevel = nullptr;
        this->mLevelChunkBuilderData = nullptr;
    }

    this->mDimension = dimension;
    this->mParent = nullptr;
    this->mOwnedParent = nullptr;
}