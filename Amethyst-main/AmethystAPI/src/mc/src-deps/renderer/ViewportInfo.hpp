#pragma once
#include <glm/vec2.hpp>

struct ViewportInfo {
public:
    glm::vec2 size;
    glm::vec2 offset;
    float minDepth;
    float maxDepth;
};