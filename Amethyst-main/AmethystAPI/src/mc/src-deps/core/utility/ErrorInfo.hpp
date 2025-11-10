#pragma once
#include <cstdint>
#include <mc/src-deps/core/utility/CallStack.hpp>

namespace Bedrock {
    template <typename E>
    class ErrorInfo {
    public:
        E mError;
        Bedrock::CallStack mCallStack;
        std::vector<ErrorInfo<E>> mBranches;
    };
}
