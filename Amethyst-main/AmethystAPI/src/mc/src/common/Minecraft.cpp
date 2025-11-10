#include <mc/src/common/Minecraft.hpp>

Level* Minecraft::getLevel() const
{
    if (!mGameSession) return nullptr;
    return mGameSession->mLevel.get();
}