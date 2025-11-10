#ifdef CLIENT
#include "hooks/client/Rendering.hpp"

#include <amethyst/runtime/ModContext.hpp>
#include <amethyst/runtime/utility/InlineHook.hpp>
#include <amethyst/runtime/events/RenderingEvents.hpp>
#include <amethyst/runtime/events/RegisterEvents.hpp>

#include <mc/src-client/common/client/renderer/block/BlockGraphics.hpp>
#include <mc/src-client/common/client/renderer/blockActor/BlockActorRendererDispatcher.hpp>
#include <mc/src-client/common/client/renderer/game/LevelRenderer.hpp>

namespace Amethyst::ClientHooks::RenderingHooks {
	Amethyst::InlineHook<decltype(&BlockGraphics::initBlocks)> _BlockGraphics_initBlocks;
	void BlockGraphics_initBlocks(ResourcePackManager& resources, const Experiments& experiments) {
		_BlockGraphics_initBlocks(resources, experiments);
		InitBlockGraphicsEvent event(resources, experiments);
		Amethyst::GetEventBus().Invoke(event);
	}

	Amethyst::InlineHook<decltype(&BlockActorRenderDispatcher::initializeBlockEntityRenderers)> _BlockActorRenderDispatcher_initializeBlockEntityRenderers;
	void BlockActorRenderDispatcher_initializeBlockEntityRenderers(
		BlockActorRenderDispatcher* self,
		const Bedrock::NotNullNonOwnerPtr<GeometryGroup>& geometryGroup,
		std::shared_ptr<mce::TextureGroup> textures,
		BlockTessellator& blockTessellator,
		const Bedrock::NotNullNonOwnerPtr<const ActorResourceDefinitionGroup>& entityResourceDefGroup,
		ResourcePackManager& resourcePackManager,
		MinecraftGameplayGraphicsResources& gameplayGraphicsResources,
		Bedrock::NotNullNonOwnerPtr<ResourceLoadManager> resourceLoadManager,
		const BaseGameVersion& version,
		const Experiments& experiments
	) {
		_BlockActorRenderDispatcher_initializeBlockEntityRenderers(
			self,
			geometryGroup,
			textures,
			blockTessellator,
			entityResourceDefGroup,
			resourcePackManager,
			gameplayGraphicsResources,
			resourceLoadManager,
			version,
			experiments
		);

		InitBlockEntityRenderersEvent event(*self, geometryGroup, textures, blockTessellator, entityResourceDefGroup, resourcePackManager, gameplayGraphicsResources, resourceLoadManager, version, experiments);
		Amethyst::GetEventBus().Invoke(event);
	}

	Amethyst::InlineHook<decltype(&LevelRenderer::renderLevel)> _LevelRenderer_renderLevel;
	void LevelRenderer_renderLevel(LevelRenderer* self, ScreenContext& screenContext, FrameRenderObject& frameRenderObj) {
		Amethyst::EventBus& bus = Amethyst::GetEventBus();
		BeforeRenderLevelEvent beforeEvent(*self, screenContext, frameRenderObj);
		bus.Invoke(beforeEvent);
		_LevelRenderer_renderLevel(self, screenContext, frameRenderObj);
		AfterRenderLevelEvent afterEvent(*self, screenContext, frameRenderObj);
		bus.Invoke(afterEvent);
	}

	void Initialize() {
		auto& hooks = Amethyst::GetHookManager();
		HOOK(BlockGraphics, initBlocks);
		HOOK(BlockActorRenderDispatcher, initializeBlockEntityRenderers);
		HOOK(LevelRenderer, renderLevel);
	}
}
#endif