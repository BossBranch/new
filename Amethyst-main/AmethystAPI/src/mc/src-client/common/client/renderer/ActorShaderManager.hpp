/// @symbolgeneration
#pragma once
#include <amethyst/Imports.hpp>

#include <mc/src-deps/minecraftrenderer/renderer/MaterialPtr.hpp>
#include <mc/src-deps/core/math/Color.hpp>

class Actor;

// That vptr is actually from BaseActorRenderer, 
// but since we are defining the destructor as default 
// and the _getOverlayColor is the same as in BaseActorRenderer, 
// we can just put it here
/// @vptr {0x4CEF830}
class ActorShaderManager {
public:
    /* this + 8  */ mce::MaterialPtr mEntityMaterial;
    /* this + 24 */ mce::MaterialPtr mTransparentEntityMaterial;
    /* this + 40 */ mce::MaterialPtr mStaticMaterial;

    ActorShaderManager() = default;

    virtual ~ActorShaderManager() = default;

	mce::MaterialPtr& getEntityMaterial();
	mce::MaterialPtr& getTransparentEntityMaterial();
	mce::MaterialPtr& getStaticEntityMaterial();
	
    /// @vidx {1}
    MC virtual mce::Color _getOverlayColor(Actor& entity, float alpha) const;
};