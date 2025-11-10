/// @symbolgeneration
#pragma once

#include <memory>
#include <mc/src/common/world/item/registry/ItemRegistryRef.hpp>
#include <mc/src/common/world/level/ILevel.hpp>
#include <mc/src/common/world/level/BlockSourceListener.hpp>
#include <mc/src/common/world/level/IWorldRegistriesProvider.hpp>
#include <mc/src-deps/gamerefs/OwnerPtr.hpp>
#include <mc/src/common/world/level/dimension/DimensionFactory.hpp>
#include <amethyst/Imports.hpp>

// client code included on server?
#include <mc/src-client/common/client/renderer/texture/BaseLightTextureImageBuilder.hpp>

class PacketSender;
class TrimMaterialRegistry;
class TrimPatternRegistry;

/// @vptr {0x4DFA540}
class Level : public ILevel, public BlockSourceListener, public IWorldRegistriesProvider {
public:
    /* this + 40   */ std::byte padding40[800];
    /* this + 840  */ const ItemRegistryRef mItemRegistry;
    /* this + 856  */ std::byte padding856[1824];
    /* this + 2680 */ std::shared_ptr<TrimPatternRegistry> mTrimPatternRegistry;
    /* this + 2696 */ std::shared_ptr<TrimMaterialRegistry> mTrimMaterialRegistry;
    /* this + 2712 */ std::byte padding2712[152];
    /* this + 2864 */ PacketSender* mPacketSender;
    /* this + 2872 */ std::byte padding2872[2648];
    /* this + 5520 */ bool isClientSide;
    /* this + 5521 */ std::byte padding5521[887];
    /* this + 6408 */ std::shared_ptr<OwnerPtr<DimensionFactory>> mDimensionFactory;     // its actually a gsl::not_null but compiler hates that despite the fact we don't construct level
    /* this + 6424 */ std::byte padding6424[6512 - 6424];
    /* this + 6512 */ Factory<BaseLightTextureImageBuilder, Level&, Scheduler&> mLightTextureImageBuilderFactory;

    MC static uintptr_t $vtable_for_this;

	/**@vidx {i}*/
    MC virtual void tick() override;
};

// 1.21.0.3
static_assert(offsetof(Level, mPacketSender) == 2864);
static_assert(offsetof(Level, isClientSide) == 5520);
static_assert(offsetof(Level, mTrimPatternRegistry) == 2680);
static_assert(offsetof(Level, mTrimMaterialRegistry) == 2696);