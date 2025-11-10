#pragma once
#include <amethyst/runtime/platform/Platform.hpp>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

// base class for anything windows, things can be further specialized for server/client if needed

class WindowsPlatformCommon : public Amethyst::Platform {
public:
    WindowsPlatformCommon(HANDLE mcThreadHandle);

    virtual void Initialize() override;
    virtual void Shutdown() override;
    virtual void ShutdownWaitForInput() override;

    virtual bool HasRequestedStop() const override;
    virtual bool HasRequestedHotReload() const override;

    virtual void AttachDebugger() const override;
    virtual void PauseGameThread() const override;
    virtual void ResumeGameThread() const override;
    virtual void InitializeConsole() const override;

private:
    HANDLE mMcThreadHandle;
};