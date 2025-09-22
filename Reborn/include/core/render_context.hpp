#pragma once
#include <glm/mat4x4.hpp>
#include "quad_mesh.hpp"
#include "sprite_renderer.hpp"

namespace core {
    struct RenderContext {
        QuadMesh quad;
        SpriteRenderer renderer;
        glm::mat4 projection{ 1.f };

        void init() { quad.create(); renderer.create(); }
    };
}