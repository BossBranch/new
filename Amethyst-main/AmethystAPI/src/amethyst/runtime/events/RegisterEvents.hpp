#pragma once
#include <amethyst/runtime/events/EventBus.hpp>
#include <mc/src-deps/core/utility/NonOwnerPointer.hpp>
#include <amethyst/game/CreativeItemRegistry.hpp>

namespace mce {
class TextureGroup;
};

class ItemRegistry;
class BlockDefinitionGroup;
class ResourcePackManager;
class Experiments;
class GeometryGroup;
class BlockTessellator;
class ActorResourceDefinitionGroup;
class ResourceLoadManager;
class BaseGameVersion;
class MinecraftGameplayGraphicsResources;
class BlockActorRenderer;
class BlockActorRenderDispatcher;

class RegisterItemsEvent : public BaseEvent {
public:
    ItemRegistry& itemRegistry;
    Amethyst::CreativeItemRegistry& mCreativeItemRegistry;

    RegisterItemsEvent(ItemRegistry& registry, Amethyst::CreativeItemRegistry& creativeItemRegistry) 
        : itemRegistry(registry), mCreativeItemRegistry(creativeItemRegistry) {}
};

class RegisterBlocksEvent : public BaseEvent {
public:
    BlockDefinitionGroup& blockDefinitions;

    RegisterBlocksEvent(BlockDefinitionGroup& blockDefs) 
        : blockDefinitions(blockDefs) {}
};

class InitBlockGraphicsEvent : public BaseEvent {
public:
    ResourcePackManager& resources;
    const Experiments& experiments;

    InitBlockGraphicsEvent(ResourcePackManager& resources, const Experiments& experiments)
        : resources(resources), experiments(experiments) {}
};

// Yeah, that's massive
class InitBlockEntityRenderersEvent : public BaseEvent {
public:
    BlockActorRenderDispatcher& renderDispatcher;
    const Bedrock::NotNullNonOwnerPtr<GeometryGroup>& geometryGroup;
    std::shared_ptr<mce::TextureGroup> textures;
    BlockTessellator& blockTessellator;
    const Bedrock::NotNullNonOwnerPtr<const ActorResourceDefinitionGroup>& entityResourceDefGroup;
    ResourcePackManager& resourcePackManager;
    MinecraftGameplayGraphicsResources& gameplayGraphicsResources;
    Bedrock::NotNullNonOwnerPtr<ResourceLoadManager> resourceLoadManager;
    const BaseGameVersion& version;
    const Experiments& experiments;

    InitBlockEntityRenderersEvent(
        BlockActorRenderDispatcher& renderDispatcher,
        const Bedrock::NotNullNonOwnerPtr<GeometryGroup>& geometryGroup,
        std::shared_ptr<mce::TextureGroup> textures,
        BlockTessellator& blockTessellator,
        const Bedrock::NotNullNonOwnerPtr<const ActorResourceDefinitionGroup>& entityResourceDefGroup,
        ResourcePackManager& resourcePackManager,
        MinecraftGameplayGraphicsResources& gameplayGraphicsResources,
        Bedrock::NotNullNonOwnerPtr<ResourceLoadManager> resourceLoadManager,
        const BaseGameVersion& version,
        const Experiments& experiments
    ) : 
        renderDispatcher(renderDispatcher),
        geometryGroup(geometryGroup),
        textures(textures),
        blockTessellator(blockTessellator),
        entityResourceDefGroup(entityResourceDefGroup),
        resourcePackManager(resourcePackManager),
        gameplayGraphicsResources(gameplayGraphicsResources),
        resourceLoadManager(resourceLoadManager),
        version(version),
        experiments(experiments)
    {}
};