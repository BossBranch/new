#pragma once
#include <memory>
#include <type_traits>
#include "mc/src-client/common/client/game/IClientInstance.hpp"
#include "mc/src-deps/core/utility/NonOwnerPointer.hpp"
#include "mc/src-client/common/client/gui/screens/models/MinecraftScreenModel.hpp"
#include "mc/src-client/common/client/gui/screens/SceneFactory.hpp"
#include "mc/src-deps/core/utility/ServiceLocator.hpp"

class IAdvancedGraphicsOptions;
class MinecraftGame;
class ClientInstance;
class SceneCreationUtils {
public:
    template <typename T, typename... Args>
    requires std::is_base_of<MinecraftScreenModel, T>::value && std::constructible_from<T, const MinecraftScreenModel::Context&, Args...>
    static std::shared_ptr<T> _createModel(SceneFactory& factory, MinecraftGame& game, ClientInstance& client, const Bedrock::NotNullNonOwnerPtr<IAdvancedGraphicsOptions>& advancedGraphicOptions, Args&&... args)
    {
        auto& appConfigs = *ServiceLocator<AppConfigs>::mService;

        MinecraftScreenModel::Context ctx {
            .mMinecraft = game,
            .mClient = client,
            .mAdvancedGraphicsOptions = advancedGraphicOptions,
            .mSceneStack = factory.getCurrentSceneStack(),
            .mSceneFactory = factory,
            .mCapabilities = nullptr
        };

        return std::make_shared<T>(ctx, std::forward<Args>(args)...);
    }
};