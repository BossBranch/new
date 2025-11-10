/// @symbolgeneration
#pragma once
#include "amethyst/Imports.hpp"
#include "mc/src-deps/core/utility/NonOwnerPointer.hpp"
#include "mc/src-client/common/client/gui/screens/SceneStack.hpp"

class MinecraftGame;
class ClientInstance;
class IAdvancedGraphicsOptions;
class AbstractScene;
class BaseScreen;
class UIScene;
class ScreenController;
class SceneFactory {
public:
    ClientInstance& mClient;
    MinecraftGame& mMinecraft;
    std::byte padding24[0x8];
    Bedrock::NonOwnerPointer<IAdvancedGraphicsOptions> mAdvancedGraphicOptions;

    /// @signature {48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 41 56 48 83 EC ? 48 8B EA 33 F6}
    MC Bedrock::NonOwnerPointer<SceneStack> getCurrentSceneStack();

    /// @signature {48 8B C4 55 53 56 57 41 54 41 55 41 56 41 57 48 8D A8 ? ? ? ? 48 81 EC ? ? ? ? 0F 29 70 ? 0F 29 78 ? 44 0F 29 40 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B F1}
    MC std::shared_ptr<UIScene> createUIScene(MinecraftGame& game, ClientInstance& client, const std::string& entryPoint, std::shared_ptr<ScreenController> controller);

    /// @signature {48 89 5C 24 ? 4C 89 44 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 83 EC ? 49 8B F0}
    MC std::shared_ptr<AbstractScene> _createScreen(std::shared_ptr<BaseScreen> screen);

    virtual ~SceneFactory() = default;
};