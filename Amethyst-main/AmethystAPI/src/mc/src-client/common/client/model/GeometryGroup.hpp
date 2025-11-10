#pragma once
#include <memory>
#include <unordered_map>
#include <mutex>

#include <mc/src-deps/core/string/StringHash.hpp>
#include <mc/src-client/common/client/model/GeometryInfo.hpp>
#include <mc/src-deps/core/utility/NonOwnerPointer.hpp>
    
class GeometryGroup : 
    public std::enable_shared_from_this<GeometryGroup>, 
    public Bedrock::EnableNonOwnerReferences 
{
public:
    /* this + 40  */ std::unordered_map<HashedString, std::shared_ptr<GeometryInfo>> mGeometries;
    /* this + 104 */ std::mutex mGeometryLock;

	std::shared_ptr<GeometryInfo> getGeometry(const HashedString& key) {
        std::scoped_lock lock(mGeometryLock);

        auto it = mGeometries.find(key);
        if (it != mGeometries.end()) {
            return it->second;
        }

        return nullptr;
    }
};

static_assert(offsetof(GeometryGroup, mGeometries) == 40);
static_assert(offsetof(GeometryGroup, mGeometryLock) == 104);