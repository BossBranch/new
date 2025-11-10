/// @symbolgeneration
#pragma once
#include <memory>
#include "amethyst/Imports.hpp"
#include <mc/src-client/common/client/renderer/TextureGroup.hpp>
#include <mc/src-client/common/client/gui/gui/FontHandle.hpp>
#include <mc/src-client/common/client/world/System.hpp>

// class MinecraftGame : public BedrockEngine::AppIsland, App, IMinecraftGame, LevelListener,
//                             ResourcePackListener, OptionsObserver, ActiveDirectoryIdentityObserver

class MinecraftInputHandler;
class FontRepository;
class ResourcePackRepository;
class ResourcePackManager;

class AbstractTextureAccessor {
public:
	uintptr_t** vtable;

	cg::ImageBuffer& getCachedImageOrLoadSync(ResourceLocation& loc, bool a2) {
		using function = decltype(&AbstractTextureAccessor::getCachedImageOrLoadSync);
		auto func = std::bit_cast<function>(vtable[2]);
		return (this->*func)(loc, a2);
	}
};

class RuntimeImageGeneratorInfo {
public:
    std::string unk0;
    ResourceLocation loc;
    const std::function<void(AbstractTextureAccessor&, cg::ImageBuffer&)> factory;

    RuntimeImageGeneratorInfo(const std::string& unk0_, const ResourceLocation& loc_, const std::function<void(AbstractTextureAccessor&, cg::ImageBuffer&)>& factory_)
        : unk0(unk0_)
        , loc(loc_)
        , factory(factory_) {}
};

class TextureAtlas : public Bedrock::EnableNonOwnerReferences {
public:
	/// @signature {40 53 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 48 8B DA 48 89 54 24 ? 48 8B 91 ? ? ? ? 48 3B 91 ? ? ? ? 74 ? 33 C0 48 89 02 48 89 42 ? 48 39 43 ? 74 ? 48 8B 03 48 89 02 48 8B 43 ? 48 89 42 ? F0 FF 40 ? 48 83 81}
	MC void addRuntimeImageGenerator(std::weak_ptr<RuntimeImageGeneratorInfo> a2);
};

class MinecraftGame {
public:
	/* this + 0    */ uintptr_t** vtable;
	/* this + 8    */ std::byte padding8[352 - 8];
	/* this + 352  */ std::shared_ptr<FontRepository> mFontRepository;
	/* this + 368  */ std::byte padding368[1920 - 1560];
	/* this + 728  */ ResourcePackManager* mResourcePackManager;
	/* this + 736  */ std::byte padding736[2088 - 736];
	/* this + 2088 */ std::shared_ptr<mce::TextureGroup> mTextures;
	/* this + 2104 */ std::byte padding1936[2272 - 2104];
	/* this + 2272 */ std::unique_ptr<ResourcePackRepository> mResourcePackRepository;
	/* this + 2280 */ std::byte padding2296[3328 - 2280];
	/* this + 3328 */ std::unique_ptr<MinecraftInputHandler> mInput;
	/* this + 3336 */ std::byte padding3336[3768 - 3336];
	// /* this + 3496 */ std::unique_ptr<TextureAtlas> mTextureAtlas;
	// /* this + 3504 */ std::unique_ptr<TextureAtlas> mItemTextureAtlas;
	// /* this + 3512 */ std::byte padding3512[3768 - 3512];
	/* this + 3768 */ World::System* mWorldSystem;
	/* this + 3776 */ std::byte padding3744[3912 - 3776];
	/* this + 3912 */ FontHandle mFontHandle;
	/* this + 3984 */ FontHandle mRuneFontHandle;
	/* this + 4056 */ FontHandle mUnicodeFontHandle;
	/* this + 4128 */ FontHandle mSmoothFontLatinHandle;
	/* this + 4200 */ FontHandle mUIFontHandle;

	/// @signature {48 89 5C 24 ? 48 89 7C 24 ? 55 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B FA 48 8B D9 0F 57 C0 0F 11 45}
	MC void onActiveResourcePacksChanged(ResourcePackManager& resourcePackManager);

	/// @signature {48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 4C 8B E9 45 33 F6}
	MC void onAppSuspended();
};

// 1.21.0.3
static_assert(offsetof(MinecraftGame, mTextures) == 2088);
static_assert(offsetof(MinecraftGame, mFontHandle) == 3912);