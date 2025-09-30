#pragma once
#include <GLFW/glfw3.h>
#include "spriteset.hpp"
#include "texture.hpp"

namespace ecs {
    struct KeyEdge {
        int key; bool isMouse; bool prevDown = false;
        KeyEdge(int k, bool mouse = false) : key(k), isMouse(mouse) {}
        bool pressed(GLFWwindow* w);
    };
    struct InputSystem {
        int controlledIndex = -1;
        KeyEdge fireKey{ GLFW_MOUSE_BUTTON_1,true };
        KeyEdge enemyKey{ GLFW_KEY_E };
        void update(SpriteSet& S, GLFWwindow* win, float dt,
            const core::Texture2D* bulletTex, const core::Texture2D* enemyTex,
            int worldW, int worldH, int zoom, int windowW, int windowH);
    };
}

