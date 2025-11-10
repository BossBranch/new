/// @symbolgeneration
#pragma once
#include <string>
#include <amethyst/Imports.hpp>

class SystemInfo {
public:
	std::string mName;
	//Dependencies mDependencies;
	//std::vector<ComponentInfo>* (__fastcall* mGenerateDetailedInfo)(std::vector<ComponentInfo>* result);
};

struct EntitySystemTickingMode
{
	bool mNormalTick;
	bool mSingleTick;
};

class IEntitySystems {
public:
    /// @signature {40 53 48 83 EC ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 44 24 ? 49 8B D8 48 89 5C 24 ? 48 8B 01}
    MC void registerTickingSystem(void* initializerList, void* tickingSystem, const SystemInfo& systemInfo, EntitySystemTickingMode mode);
};