#pragma once

struct ActorWalkAnimationComponent
{
    float mWalkAnimSpeedMultiplier;
    float mWalkAnimSpeedO;
    float mWalkAnimSpeed;
    float mWalkAnimPos;

    ActorWalkAnimationComponent()
        : mWalkAnimSpeedMultiplier(1.0f), mWalkAnimSpeedO(0.0f), mWalkAnimSpeed(0.0f), mWalkAnimPos(0.0f) {}

    ActorWalkAnimationComponent(const ActorWalkAnimationComponent& other) {
        mWalkAnimSpeedMultiplier = other.mWalkAnimSpeedMultiplier;
        mWalkAnimSpeedO = other.mWalkAnimSpeedO;
        mWalkAnimSpeed = other.mWalkAnimSpeed;
        mWalkAnimPos = other.mWalkAnimPos;
    }
};