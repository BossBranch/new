#pragma once
#include "amethyst/runtime/mod/Mod.hpp"
#include "amethyst/runtime/mod/ModGraph.hpp"

namespace Amethyst {
class ModLoader {
    AmethystContext* mContext = nullptr;
    std::vector<std::shared_ptr<Mod>> mMods;
    std::vector<ModError> mErrors;

public:
    ModLoader(AmethystContext* ctx);
    ~ModLoader();

    ModLoader(const ModLoader&) = delete;
    ModLoader& operator=(const ModLoader&) = delete;
    ModLoader(ModLoader&&) = delete;
    ModLoader& operator=(ModLoader&&) = delete;

    void LoadGraph(const ModGraph& graph);
    std::weak_ptr<const Mod> LoadSingle(const std::shared_ptr<const ModInfo>& info);
    void UnloadAll();
    void Unload(const std::shared_ptr<const ModInfo>& info);
    void Unload(const std::string& uuid);

    std::weak_ptr<const Mod> GetModByUUID(const std::string& uuid) const;
    std::weak_ptr<const Mod> GetModByNamespace(const std::string& modNamespace) const;

    std::vector<std::weak_ptr<const Mod>> GetMods() const;
    size_t GetModCount() const;

    const std::vector<ModError>& GetErrors() const;
    bool HasErrors() const;
};
} // namespace Amethyst