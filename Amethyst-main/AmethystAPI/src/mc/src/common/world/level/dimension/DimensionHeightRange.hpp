#pragma once
#include "mc/src/common/CommonTypes.hpp"

class DimensionHeightRange {
public:
    Height mMin;
    Height mMax;

    DimensionHeightRange(short min, short max) 
        : mMin(min), mMax(max) {}
};