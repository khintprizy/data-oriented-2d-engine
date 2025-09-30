#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "texture.hpp"
#include "constants.hpp"

namespace ecs {
    struct SpriteSet {
        std::vector<const core::Texture2D*> tex;
        std::vector<glm::vec2> pos, size, origin, vel;
        std::vector<float> rotDeg, lifetime;
        std::vector<glm::vec4> tint;
        std::vector<uint8_t> alive, type;
        std::vector<int> freeIndices;
        bool isPlayerDead = false;

        int add(const core::Texture2D* t, glm::vec2 p, glm::vec2 s,
            float r = 0.f, glm::vec2 o = { 0.5f,0.5f }, glm::vec4 c = { 1,1,1,1 },
            glm::vec2 v = { 0,0 }, float life = -1.f, uint8_t et = core::ET_None);
        int spawnProjectile(const core::Texture2D* t, glm::vec2 p, glm::vec2 v,
            glm::vec2 s = { 8,16 }, float life = 2.f);
        int spawnEnemy(const core::Texture2D* t, glm::vec2 p, glm::vec2 v,
            glm::vec2 s = { 48,48 }, float life = -1.f);
        void kill(int i);
        void killThePlayer(int i);
        int count() const { return (int)pos.size(); }
    };
}