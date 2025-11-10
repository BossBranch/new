#pragma once
#include "platforms/WindowsPlatformCommon.hpp"

class WindowsClientPlatform : public WindowsPlatformCommon {
public:
    WindowsClientPlatform(HANDLE mcThreadHandle);

    virtual Amethyst::PlatformType GetPlatformType() const override;
    virtual fs::path GetComMojangPath() const override;
    virtual fs::path GetAmethystFolder() const override;
	virtual std::string GetPlatformFolderName() override;

	virtual uintptr_t GetMinecraftBaseAddress() const override;
	virtual size_t GetMinecraftSize() const override;
};