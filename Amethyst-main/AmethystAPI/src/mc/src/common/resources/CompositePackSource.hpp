#pragma once
#include <vector>
#include "mc/src/common/resources/PackSource.hpp"

class CompositePackSource : public PackSource {
public:
    std::vector<PackSource*> mPackSources;
};