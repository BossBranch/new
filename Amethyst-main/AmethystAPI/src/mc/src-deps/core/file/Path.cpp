#include "mc/src-deps/core/file/Path.hpp"

Core::Path::Path(const std::string& path)
{
    mPathPart.mUtf8StdString = path;
}

Core::Path::Path()
{
    mPathPart.mUtf8StdString = std::string();
}
