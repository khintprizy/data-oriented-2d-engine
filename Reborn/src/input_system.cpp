#include "systems/input_system.hpp"
#include "constants.hpp"
#include "types.hpp"
#include <glm/glm.hpp>

namespace ecs {
    bool KeyEdge::pressed(GLFWwindow* w) {
        bool down = isMouse ? (glfwGetMouseButton(w, key) == GLFW_PRESS)
            : (glfwGetKey(w, key) == GLFW_PRESS);
        bool rising = down && !prevDown; prevDown = down; return rising;
    }

    void InputSystem::update(SpriteSet& S, GLFWwindow* win, float dt,
        const core::Texture2D* bulletTex, const core::Texture2D* enemyTex,
        int worldW, int worldH, int zoom, int windowW, int windowH)
    {
        if (controlledIndex >= 0 && !S.isPlayerDead) {
            const float speed = 10.f, deltaMult = 100000.f;
            glm::vec2 d(0);
            if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) d.x -= 1;
            if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) d.x += 1;
            if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) d.y -= 1;
            if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) d.y += 1;
            if (d.x != 0 || d.y != 0) d = glm::normalize(d);
            S.vel[controlledIndex] = d * speed * dt * deltaMult;
        }

        if (fireKey.pressed(win) && !S.isPlayerDead) {
            double mx, my; glfwGetCursorPos(win, &mx, &my);
            float worldX = (float)mx * zoom, worldY = ((float)windowH - (float)my) * zoom;

            auto pc = core::centerOf(S.pos[controlledIndex], S.size[controlledIndex], S.origin[controlledIndex]);
            glm::vec2 dir = { worldX,worldY } - pc; float len = glm::length(dir);
            if (len < .3f) return; dir /= len;
            glm::vec2 right = { -dir.y, dir.x };

            float playerR = core::radiusOf(S.size[controlledIndex]);
            float bulletR = 8.f;

            glm::vec2 spawnPos = pc + (dir * (playerR + bulletR + 2.f + core::kMuzzleForward))
                + (right * core::kMuzzleRight);

            float bulletSpeed = 1300.f; glm::vec2 v = dir * bulletSpeed;
            glm::vec2 bulletSize = { 24,48 };

            int bi = S.spawnProjectile(bulletTex, spawnPos, v, bulletSize, 2.f);
            S.rotDeg[bi] = core::angleDegFromVelocity(v) + core::kBulletFacingOffsetDeg;
        }

        if (enemyKey.pressed(win)) {
            float x = (float)(rand() % worldW), y = (float)(rand() % worldH);
            S.spawnEnemy(enemyTex, { x,y }, { 0,0 }, { 120,120 }, -1.f);
        }
    }
}
