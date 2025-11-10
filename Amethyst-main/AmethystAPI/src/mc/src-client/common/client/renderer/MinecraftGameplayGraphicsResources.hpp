#pragma once
#include <memory>
#include <cstddef>

namespace mce {
	class BufferResourceService;
}

class MinecraftGameplayGraphicsResources {
public:
	/* this + 0   */ std::byte padding0[304 - 0];
	/* this + 304 */ std::shared_ptr<mce::BufferResourceService> mBufferResourceService;
};

static_assert(offsetof(MinecraftGameplayGraphicsResources, mBufferResourceService) == 304);