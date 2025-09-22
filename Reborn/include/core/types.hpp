#pragma once
#include <glm/glm.hpp>
//#include <algorithm>

namespace core
{
    inline glm::vec2 centerOf(const glm::vec2& pos, const glm::vec2& size, const glm::vec2& origin) {
        return pos + (glm::vec2{ 0.5f,0.5f } - origin) * size;
    }
    inline float radiusOf(const glm::vec2& size) {
        return 0.5f * std::min(size.x, size.y);
    }
    inline float angleDegFromVelocity(const glm::vec2& v) {
        if (v.x == 0.f && v.y == 0.f) return 0.f;
        return glm::degrees(std::atan2(v.y, v.x));
    }
}