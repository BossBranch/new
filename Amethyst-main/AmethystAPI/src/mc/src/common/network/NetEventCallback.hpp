#pragma once
#include <mc/src-deps/core/utility/NonOwnerPointer.hpp>

class NetEventCallback : public Bedrock::EnableNonOwnerReferences {
public:
    virtual ~NetEventCallback();
};