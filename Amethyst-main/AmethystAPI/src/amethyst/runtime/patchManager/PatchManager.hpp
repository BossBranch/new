#pragma once
#include <cstdint>
#define WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include <vector>
namespace Amethyst {
	class PatchManager {
	public:		
		PatchManager() = default;
        PatchManager(const PatchManager&) = delete;
        PatchManager(PatchManager&&) = delete;
        PatchManager& operator=(const PatchManager&) = delete;
        PatchManager& operator=(PatchManager&&) = delete;
        void ApplyPatch(uintptr_t address, uint8_t* patch, size_t size);
        ~PatchManager();

    private:

		struct OriginalMemory {
			uint8_t* original = nullptr;
			size_t size = 0;
		};

		struct Patch {
            uintptr_t address = 0x0;
            OriginalMemory original = {};
		};

		std::vector<Patch> mPatches;

		friend class AmethystRuntime;
	};
}