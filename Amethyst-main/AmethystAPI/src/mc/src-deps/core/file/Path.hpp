#pragma once
#include <string>

namespace Core {
class PathPart {
public:
    std::string mUtf8StdString;
};

template <class ContainerType>
class PathBuffer {
public:
    ContainerType mContainer;

    PathBuffer() 
        : mContainer() {}

    PathBuffer(const ContainerType& container) 
        : mContainer(container) {}
};

class Path {
public:
    PathPart mPathPart;
    Path(const std::string&);
    Path();


};
} // namespace Core
