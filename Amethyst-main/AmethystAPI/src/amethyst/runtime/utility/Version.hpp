#pragma once
#include "neargye/semver.hpp"

namespace Amethyst {
using Version = semver::version<int, int, int>;
using Range = semver::range_set<int, int, int>;
} // namespace Amethyst