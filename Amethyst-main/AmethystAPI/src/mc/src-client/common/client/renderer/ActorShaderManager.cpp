#include "ActorShaderManager.hpp"
#include <mc/src-client/common/client/renderer/RenderMaterialGroup.hpp>

mce::MaterialPtr& ActorShaderManager::getEntityMaterial() {
	if (mEntityMaterial.isNull()) {
		mEntityMaterial = mce::RenderMaterialGroup::switchable.getMaterial("entity");
	}

	return mEntityMaterial;
}

mce::MaterialPtr& ActorShaderManager::getTransparentEntityMaterial() {
	if (mTransparentEntityMaterial.isNull()) {
		mEntityMaterial = mce::RenderMaterialGroup::switchable.getMaterial("entity_alphatest");
	}

	return mEntityMaterial;
}

mce::MaterialPtr& ActorShaderManager::getStaticEntityMaterial() {
	if (mStaticMaterial.isNull()) {
		mStaticMaterial = mce::RenderMaterialGroup::switchable.getMaterial("entity_static");
	}

	return mStaticMaterial;
}
