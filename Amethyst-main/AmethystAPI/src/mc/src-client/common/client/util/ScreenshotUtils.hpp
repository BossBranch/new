#pragma once
#include <mc/src-deps/core/file/Path.hpp>
#include <filesystem>

enum class ScreenshotPostProcessFilter : int32_t {
    None = 0
};

struct ScreenshotOptions {
public:
    bool mCropToRatio;
    int mWidthRatio;
    int mHeightRatio;
    unsigned int mMaxWidth;
    unsigned int mMaxHeight;
    bool mRestrictScreenshotSize;
    bool mApplySquareFrame;
    Core::PathBuffer<std::string> mRequestedFileName;
    Core::PathBuffer<std::string> mRequestedFilePath;
    Core::PathBuffer<std::string> mRequestedExtension;
    bool mReplaceImage;
    bool mUseScreenshotsFolder;
    bool mHideUI;
    bool mLogRequest;
    bool mWriteScreenshotToFile;
    bool mIsSavegameScreenshot;
    Core::PathBuffer<std::string> mOutFileName;
    Core::PathBuffer<std::string> mOutFileDir;
    Core::PathBuffer<std::string> mOutExtension;
    ScreenshotPostProcessFilter mPostProcessFilter;
    Core::PathBuffer<std::string> mScreenshotBorderResourcePath;

    ScreenshotOptions(uint32_t width, uint32_t height, const std::string& outputFilePath) {
        mCropToRatio = false;
        mWidthRatio = 0;
        mHeightRatio = 0;
        mMaxWidth = width;
        mMaxHeight = height;
        mRestrictScreenshotSize = true;
        mApplySquareFrame = false;

        namespace fs = std::filesystem;
        fs::path outPath(outputFilePath);

        // Extract dir, name, extension using filesystem
        std::string dir = outPath.parent_path().string();
        std::string name = outPath.stem().string();
        std::string ext = outPath.has_extension() ? outPath.extension().string().substr(1) : "png"; // strip dot

        mRequestedFileName = Core::PathBuffer<std::string>(name);
        mRequestedFilePath = Core::PathBuffer<std::string>(dir);
        mRequestedExtension = Core::PathBuffer<std::string>(ext);

        mReplaceImage = true;
        mUseScreenshotsFolder = false;
        mHideUI = true;
        mLogRequest = false;
        mWriteScreenshotToFile = true;
        mIsSavegameScreenshot = false;

        mOutFileName = Core::PathBuffer<std::string>(name);
        mOutFileDir = Core::PathBuffer<std::string>(dir);
        mOutExtension = Core::PathBuffer<std::string>(ext);

        mPostProcessFilter = ScreenshotPostProcessFilter::None;
        mScreenshotBorderResourcePath = Core::PathBuffer<std::string>("");
    }
};