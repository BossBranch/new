#include "amethyst/runtime/mod/ModRepository.hpp"
#include "amethyst/Log.hpp"

namespace Amethyst {
void ModRepository::ScanDirectory(const fs::path& directory, bool skipRuntimes)
{
    Clear();
	if (!fs::exists(directory) || !fs::is_directory(directory)) {
        throw std::invalid_argument("Provided path is not a valid directory: " + directory.generic_string());
	}
	for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (entry.is_directory() || entry.path().filename() != "mod.json")
            continue;
        auto result = ModInfo::FromFile(entry.path());
        if (!result) {
            mErrors.push_back(result.error());
            continue;
        }
        auto& modInfo = *result;
        if (modInfo.IsRuntime && skipRuntimes) {
            continue;
        }
        if (mMods.contains(modInfo.UUID)) {
            Log::Warning("Mod with UUID '{}' already exists in repository, skipping duplicate from '{}'", modInfo.UUID, entry.path().generic_string());
            continue;
        }
        mMods.emplace(modInfo.UUID, std::make_shared<const ModInfo>(modInfo));
	}
}

void ModRepository::Clear() {
    mMods.clear();
    mErrors.clear();
}

const ModInfoMap& ModRepository::GetMods() const {
    return mMods;
}

const std::vector<ModError>& ModRepository::GetErrors() const {
    return mErrors;
}

std::shared_ptr<const ModInfo> ModRepository::GetModByUUID(const std::string& uuid) const
{
    auto it = mMods.find(uuid);
    if (it != mMods.end()) {
        return it->second;
    }
    return nullptr;
}

std::shared_ptr<const ModInfo> ModRepository::GetModByNamespace(const std::string& modNamespace) const
{
    for (const auto& [uuid, mod] : mMods) {
        if (mod->Namespace == modNamespace) {
            return mod;
        }
    }
    return nullptr;
}

void Amethyst::ModRepository::AddMod(const ModInfoMap::const_iterator& pos, const std::shared_ptr<const ModInfo>& modInfo)
{
    mMods.insert(pos, { modInfo->UUID, modInfo });
}

bool ModRepository::HasModUUID(const std::string& uuid) const {
    return mMods.contains(uuid);
}

bool ModRepository::HasModNamespace(const std::string& modNamespace) const {
    for (const auto& [uuid, mod] : mMods) {
        if (mod->Namespace == modNamespace) {
            return true;
        }
    }
    return false;
}

bool ModRepository::HasErrors() const
{
    return !mErrors.empty();
}

size_t ModRepository::GetModCount() const {
    return mMods.size();
}
} // namespace Amethyst