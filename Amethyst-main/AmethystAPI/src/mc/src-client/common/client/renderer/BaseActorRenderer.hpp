/// @symbolgeneration
#pragma once
#include <mc/src-client/common/client/renderer/ActorShaderManager.hpp>

/// @vptr {0x4CEF830}
class BaseActorRenderer : public ActorShaderManager {
public:
    /* this + 56  */ mce::MaterialPtr mNameTagMat;
    /* this + 72  */ mce::MaterialPtr mDepthTestedNameTagMat;
    /* this + 88  */ mce::MaterialPtr mDepthTestedNameTextMat;
    /* this + 104 */ mce::MaterialPtr mDepthTestedHealthMat;

    /// @signature {48 89 5C 24 ? 48 89 74 24 ? 55 57 41 54 41 56 41 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 4C 8B F1 48 89 4D ? 45 33 E4 4C 89 61}
    MC BaseActorRenderer();

    /// @vidx {0}
    MC virtual ~BaseActorRenderer() override;
	
    /// @vidx {inherit}
    MC virtual mce::Color _getOverlayColor(Actor& entity, float alpha) const override;
};