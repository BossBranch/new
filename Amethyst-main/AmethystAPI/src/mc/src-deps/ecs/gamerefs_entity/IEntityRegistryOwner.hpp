#pragma once
#include <mc/src-deps/core/utility/NonOwnerPointer.hpp>
#include <mc/src-deps/gamerefs/StackRefResult.hpp>

class EntityRegistry;

class IEntityRegistryOwner : public Bedrock::EnableNonOwnerReferences {
protected:
    virtual ~IEntityRegistryOwner();
public:
    virtual StackRefResult<const EntityRegistry> getEntityRegistry() const;
    virtual StackRefResult<EntityRegistry> getEntityRegistry();
};