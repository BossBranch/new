/// @symbolgeneration
#pragma once
#include "amethyst/Imports.hpp"

#include <memory>
#include "mc/src-deps/core/utility/NonOwnerPointer.hpp"
#include "mc/src-client/common/client/gui/screens/ScreenController.hpp"

class AbstractScene;

class SceneStack : 
    public Bedrock::EnableNonOwnerReferences 
{
public:
    std::vector<std::shared_ptr<AbstractScene>> mScreenStack;

    /// @signature {48 89 54 24 ? 53 48 83 EC ? 48 8B DA C6 44 24 ? ? 0F 57 C0}
    MC void pushScreen(std::shared_ptr<AbstractScene> newScreen, bool flush);

    /// @signature {48 8B C4 48 89 58 ? 48 89 70 ? 57 48 83 EC ? 0F 57 C0 F3 0F 7F 40}
    MC void schedulePopScreen(uint32_t totalPopNumber);

    /// @signature {89 54 24 ? 4C 8B DC 53 48 81 EC}
    MC void popScreensBackTo(ui::SceneType sceneType);
};