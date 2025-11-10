/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>
#include "mc/src/common/world/containers/managers/models/ContainerManagerModel.hpp"
#include "managers/controllers/ContainerManagerController.hpp"

class Player;
class IContainerManager;

class ContainerFactory {
public:
    static void _setPlayerContainerManagerModel(Player& player, std::shared_ptr<IContainerManager> manager);
    static std::weak_ptr<IContainerManager> _getPlayerContainerManagerModel(const Player& player);

    template <typename T, typename... Args>
    requires std::is_base_of_v<IContainerManager, T>
    static std::weak_ptr<T> clientCreateContainerManagerModel(Player& player, Args&&... args) {
        auto model = std::make_shared<T>(std::forward<Args>(args)...);
        model->postInit();
        _setPlayerContainerManagerModel(player, model);
        return model;
    }

    /// @signature {48 89 5C 24 ? 55 56 57 48 8B EC 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B DA 48 8B F9 48 89 4D}
    MC static std::shared_ptr<ContainerController> createController(std::shared_ptr<ContainerModel> model);
};