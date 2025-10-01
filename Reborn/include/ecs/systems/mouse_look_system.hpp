#pragma once
#include "spriteset.hpp"
#include <GLFW/glfw3.h>

namespace ecs {
    struct MouseLookSystem {
        float facingOffsetDeg = -90.f;
        void update(SpriteSet& S, GLFWwindow* win, int playerIndex,
            float zoom, int windowW, int windowH);
    };
}

