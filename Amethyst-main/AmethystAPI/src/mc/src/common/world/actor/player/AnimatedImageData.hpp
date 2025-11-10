#pragma once
#include <mc/src-deps/core/image/Image.hpp>

namespace persona {
    enum class AnimatedTextureType : uint32_t {
        None = 0x0000,
        Face = 0x0001,
        Body32x32 = 0x0002,
        Body128x128 = 0x0003,
    };

    enum class AnimationExpression : uint32_t {
        Linear = 0x0000,
        Blinking = 0x0001,
    };
}

class AnimatedImageData {
public:
    persona::AnimatedTextureType mType;
    persona::AnimationExpression mAnimationExpression;
    mce::Image mImage;
    float mFrames;
};