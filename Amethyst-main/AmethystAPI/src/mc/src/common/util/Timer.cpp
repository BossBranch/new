#include "Timer.hpp"
#include <algorithm>

void Timer::advanceTime(float preferredFrameStep)
{
    if (mSteppingTick < 0) {
        // Grab current time in ms
        int64_t now = mGetTimeMSCallback();
        int64_t deltaMs = now - mLastMs;

        if (deltaMs > 1000) {
            int64_t sysDelta = now - mLastMsSysTime;
            if (now == mLastMsSysTime) {
                // Prevent div-by-zero
                deltaMs = 1;
                sysDelta = 1;
            }
            mLastMs = now;
            mLastMsSysTime = now;

            // Adjust smoothing factor
            float ratio = static_cast<float>(deltaMs) / static_cast<float>(sysDelta);
            mAdjustTime += (ratio - mAdjustTime) * 0.2f;
        }
        else {
            // Within reasonable delta, keep adjust as-is
            // (no change)
        }

        // Handle clock going backwards
        if (deltaMs < 0) {
            mLastMs = now;
            mLastMsSysTime = now;
        }

        // Convert to seconds
        float currentSeconds = now * 0.001f;
        float deltaSeconds = currentSeconds - mLastTimeSeconds;
        mLastTimeSeconds = currentSeconds;

        // Apply adjust factor
        float timestep = deltaSeconds * mAdjustTime;

        // Frame step alignment logic
        if (preferredFrameStep > 0.0f) {
            float remainder = mFrameStepAlignmentRemainder;
            float maxCatchup = preferredFrameStep * 4.0f;

            float correction = (preferredFrameStep - timestep) + remainder;
            float newRemainder = correction <= maxCatchup
                                     ? std::max(correction, 0.0f)
                                     : maxCatchup;

            mFrameStepAlignmentRemainder = newRemainder;
            timestep -= (remainder - newRemainder);
        }

        // Clamp timestep to [0, 0.1] seconds
        timestep = std::clamp(timestep, 0.0f, 0.1f);
        mLastTimestep = timestep;

        // Convert to ticks
        float ticksFloat = (timestep * mTimeScale * mTicksPerSecond) + mPassedTime;
        int ticksInt = static_cast<int>(ticksFloat);

        // Clamp ticks max to 10
        if (ticksInt > 10) ticksInt = 10;

        mTicks = ticksInt;
        mPassedTime = ticksFloat - static_cast<float>(ticksInt);
        mAlpha = mPassedTime;
    }
    else if (mSteppingTick > 0) {
        // Step manually
        mTicks = 1;
        mSteppingTick--;
    }
    else {
        // No ticks
        mTicks = 0;
        mPassedTime = 0.0f;
    }
}

void Timer::stepTime(float seconds, bool useTimescale)
{
    mLastTimestep = seconds;

    float ticksFloat;
    if (useTimescale) ticksFloat = (seconds * mTimeScale * mTicksPerSecond) + mPassedTime;
    else ticksFloat = (seconds * mTicksPerSecond) + mPassedTime;

    int ticksInt = static_cast<int>(ticksFloat);

    mTicks = ticksInt;
    mPassedTime = ticksFloat - static_cast<float>(ticksInt);
    mAlpha = mPassedTime;
}

void Timer::restartCurrentTick()
{
    mPassedTime = 0.0f;
    mFrameStepAlignmentRemainder = 0.0f;
    mLastTimestep = 0.0f;

    // Resync to current system time
    mLastMs = mGetTimeMSCallback();
    mLastMsSysTime = mLastMs;
    mLastTimeSeconds = static_cast<float>(mLastMs) / 1000.0f;

    // Alpha can be reset so interpolation starts fresh
    mAlpha = 0.0f;
}

float Timer::ComputeAlpha() const
{
    int64_t currentMs = mGetTimeMSCallback();
    float deltaSeconds = static_cast<float>(currentMs - mLastMs) / 1000.0f;
    deltaSeconds *= mTimeScale;
    float tickDelta = deltaSeconds * mTicksPerSecond;
    return tickDelta;
}