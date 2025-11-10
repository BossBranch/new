#include "MaterialPtr.hpp"
#include "mc/src-deps/renderer/RenderMaterialGroupBase.hpp"

mce::RenderMaterialInfo::RenderMaterialInfo(const HashedString& name)
{
    mHashedName = name;
}

mce::MaterialPtr::MaterialPtr(mce::RenderMaterialGroupBase& materialGroup, const HashedString& materialName)
{
    mRenderMaterialInfoPtr = materialGroup.getMaterialInfo(materialName);
}