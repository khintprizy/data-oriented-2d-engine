#include "spriteset.hpp"

namespace ecs {
    int SpriteSet::add(const core::Texture2D* t, glm::vec2 p, glm::vec2 s,
        float r, glm::vec2 o, glm::vec4 c, glm::vec2 v, float life, uint8_t et)
    {
        int i;
        if (!freeIndices.empty()) {
            i = freeIndices.back(); freeIndices.pop_back();
            tex[i] = t; pos[i] = p; size[i] = s; rotDeg[i] = r; origin[i] = o;
            tint[i] = c; vel[i] = v; alive[i] = 1; lifetime[i] = life; type[i] = et;
        }
        else {
            i = (int)pos.size();
            tex.push_back(t); pos.push_back(p); size.push_back(s); rotDeg.push_back(r);
            origin.push_back(o); tint.push_back(c); vel.push_back(v); alive.push_back(1);
            lifetime.push_back(life); type.push_back(et);
        }
        return i;
    }
    int SpriteSet::spawnProjectile(const core::Texture2D* t, glm::vec2 p, glm::vec2 v,
        glm::vec2 s, float life) {
        return add(t, p, s, 0.f, { 0.5f,0.5f }, { 1,1,1,1 }, v, life, core::ET_Bullet);
    }
    int SpriteSet::spawnEnemy(const core::Texture2D* t, glm::vec2 p, glm::vec2 v,
        glm::vec2 s, float life) {
        return add(t, p, s, 0.f, { 0.5f,0.5f }, { 1,1,1,1 }, v, life, core::ET_Enemy);
    }
    void SpriteSet::kill(int i) {
        if (alive[i]) { alive[i] = 0; freeIndices.push_back(i); }
    }
    void SpriteSet::killThePlayer(int i) { kill(i); isPlayerDead = true; }
}
