#include "systems/collision_system.hpp"
#include <types.hpp>
#include <constants.hpp>

namespace ecs
{
	void CollisionSystem::update(SpriteSet& S, int controlledIndex)
	{
		const int N = S.count();

		// we list alive bullets and enemies
		//std::vector<int> bullets, enemies;

		bullets.clear();
		enemies.clear();

		bullets.reserve(N);
		enemies.reserve(N);
		for (int i = 0; i < N; ++i)
		{
			if (!S.alive[i]) continue;
			if (S.type[i] == core::ET_Bullet) bullets.push_back(i);
			else if (S.type[i] == core::ET_Enemy) enemies.push_back(i);
		}


		if (!S.isPlayerDead)
		{
			if (controlledIndex >= 0 && S.alive[controlledIndex]) {
				//const glm::vec2 cP = getCenter(S, controlledIndex);
				const glm::vec2 cP = core::centerOf(S.pos[controlledIndex], S.size[controlledIndex], S.origin[controlledIndex]);
				//const float     rP = getRadius(S, controlledIndex);
				const float     rP = core::radiusOf(S.size[controlledIndex]);
				for (int ei : enemies) {
					if (!S.alive[ei]) continue;
					//const glm::vec2 cE = getCenter(S, ei);
					const glm::vec2 cE = core::centerOf(S.pos[ei], S.size[ei], S.origin[ei]);
					//const float     rE = getRadius(S, ei);
					const float     rE = core::radiusOf(S.size[ei]);
					if (colliding(cE, cP, rE, rP)) {
						S.killThePlayer(controlledIndex);
						// if player is dead, no need for other checks
						return;
					}
				}
			}
		}


		bulletCenters.resize(bullets.size());
		bulletRadii.resize(bullets.size());
		for (size_t b = 0; b < bullets.size(); ++b)
		{
			int bi = bullets[b];
			//bulletCenters[b] = getCenter(S, bi);
			bulletCenters[b] = core::centerOf(S.pos[bi], S.size[bi], S.origin[bi]);
			//bulletRadii[b] = getRadius(S, bi);
			bulletRadii[b] = core::radiusOf(S.size[bi]);
		}

		enemyCenters.resize(enemies.size());
		enemyRadii.resize(enemies.size());
		for (size_t e = 0; e < enemies.size(); ++e) {
			int ei = enemies[e];
			//enemyCenters[e] = getCenter(S, ei);
			enemyCenters[e] = core::centerOf(S.pos[ei], S.size[ei], S.origin[ei]);
			//enemyRadii[e] = getRadius(S, ei);
			enemyRadii[e] = core::radiusOf(S.size[ei]);
		}

		bool bulletsOuter = bullets.size() <= enemies.size();

		if (bulletsOuter) {
			// bullets outer, enemies inner
			for (size_t b = 0; b < bullets.size(); ++b) {
				int bi = bullets[b];
				if (!S.alive[bi]) continue;

				const glm::vec2& cB = bulletCenters[b];
				const float      rB = bulletRadii[b];

				for (size_t e = 0; e < enemies.size(); ++e) {
					int ei = enemies[e];
					if (!S.alive[ei]) continue;

					const glm::vec2& cE = enemyCenters[e];
					const float      rE = enemyRadii[e];

					if (colliding(cE, cB, rE, rB)) {
						S.kill(bi);
						S.kill(ei);
						break;
					}
				}
			}
		}
		else {
			// enemies outer, bullets inner
			for (size_t e = 0; e < enemies.size(); ++e) {
				int ei = enemies[e];
				if (!S.alive[ei]) continue;

				const glm::vec2& cE = enemyCenters[e];
				const float      rE = enemyRadii[e];

				for (size_t b = 0; b < bullets.size(); ++b) {
					int bi = bullets[b];
					if (!S.alive[bi]) continue;

					const glm::vec2& cB = bulletCenters[b];
					const float      rB = bulletRadii[b];

					if (colliding(cE, cB, rE, rB)) {
						S.kill(bi);
						S.kill(ei);
						break;
					}
				}
			}
		}
	}

	bool CollisionSystem::colliding(const glm::vec2& center1, const glm::vec2 center2, float radius1, float radius2)
	{
		glm::vec2 d = center1 - center2;
		float rsum = radius1 + radius2;

		return (glm::dot(d, d) <= rsum * rsum);
	}
}