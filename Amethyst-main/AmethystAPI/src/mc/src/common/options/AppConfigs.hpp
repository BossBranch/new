#pragma once
#include "mc/src-deps/core/utility/NonOwnerPointer.hpp"

class LevelSummary;
class ScreenCapabilitiesRepo;
class SceneStack;
class SceneFactory;

class AppConfigs : public Bedrock::EnableNonOwnerReferences {
public:
    std::function<bool(const LevelSummary&)> mCanAccessWorldCallback;
    std::unique_ptr<ScreenCapabilitiesRepo> mScreenCapabilities;
    std::function<void(const Bedrock::NotNullNonOwnerPtr<SceneStack>&, SceneFactory&)> mLeaveGameCallback;
};