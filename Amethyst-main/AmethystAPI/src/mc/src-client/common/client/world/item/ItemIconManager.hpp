#pragma once
#include <mc/src/common/world/item/ResolvedItemIconInfo.hpp>
#include <mc/src-client/common/client/renderer/TexturePtr.hpp>
#include <mc/src-client/common/client/renderer/texture/TextureAtlasItem.hpp>

class ItemIconManager {
public:
    static TextureAtlasItem* getIcon(const ResolvedItemIconInfo& iconInfo /*, bool compiledOut*/);
};