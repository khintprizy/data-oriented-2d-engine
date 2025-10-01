#include "systems/enemy_ai_system.hpp"
#include <types.hpp>
#include <constants.hpp>

namespace ecs
{
	void EnemyAISystem::update(SpriteSet& S, int playerIndex, float dt)
	{
		if (playerIndex < 0 || S.isPlayerDead || !S.alive[playerIndex]) return;

		//const glm::vec2 pc = getCenter(S, playerIndex);
		const glm::vec2 pc = core::centerOf(S.pos[playerIndex], S.size[playerIndex], S.origin[playerIndex]);
		const int N = S.count();

		for (int i = 0; i < N; ++i)
		{
			if (!S.alive[i] || S.type[i] != core::ET_Enemy) continue;

			//glm::vec2 ec = getCenter(S, i);
			glm::vec2 ec = core::centerOf(S.pos[i], S.size[i], S.origin[i]);
			glm::vec2 dir = pc - ec;
			float len2 = glm::dot(dir, dir);

			if (len2 > 0.0f)
			{
				dir *= 1.0f / std::sqrt(len2); // normalize
				S.vel[i] = dir * enemySpeed;
				S.rotDeg[i] = glm::degrees(std::atan2(dir.y, dir.x)) + facingOffsetDeg;
			}
			else
			{
				S.vel[i] = { 0,0 };
			}
		}
	}
}