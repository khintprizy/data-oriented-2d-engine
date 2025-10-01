#include <glm/gtc/constants.hpp>
#include <glm/glm.hpp>
#include "systems/mouse_look_system.hpp"

namespace ecs {
    void MouseLookSystem::update(SpriteSet& S, GLFWwindow* win, int playerIndex,
        float zoom, int windowW, int windowH)
    {
        if (S.isPlayerDead || playerIndex < 0 || playerIndex >= S.count() || S.type[playerIndex] != 1) return;
        double mx, my; glfwGetCursorPos(win, &mx, &my);
        float worldX = (float)mx * zoom, worldY = ((float)windowH - (float)my) * zoom;

        glm::vec2 pc = S.pos[playerIndex] + (glm::vec2{ 0.5f,0.5f } - S.origin[playerIndex]) * S.size[playerIndex];
        glm::vec2 dir = glm::vec2(worldX, worldY) - pc;
        if (dir.x == 0.f && dir.y == 0.f) return;
        float angleDeg = glm::degrees(std::atan2(dir.y, dir.x)) + facingOffsetDeg;
        S.rotDeg[playerIndex] = angleDeg;
    }
}
