#pragma once
#include <GLFW/glfw3.h>
#include "spriteset.hpp"

namespace ecs {
    struct MouseLookSystem {
        float facingOffsetDeg = -90.f;
        void update(SpriteSet& S, GLFWwindow* win, int playerIndex,
            float zoom, int windowW, int windowH);
    };
}

