#include "systems/movement_system.hpp"

namespace ecs
{
	void MovementSystem::update(SpriteSet& S, float dt)
	{
		const int N = S.count();
		for (int i = 0; i < N; ++i) {
			if (!S.alive[i]) continue; // Ölüyü atla. (Daha da iyisi: compact etmek.)
			S.pos[i] += S.vel[i] * dt;

			// Ýstersen ucuz bir davranýþ:
			 //S.rotDeg[i] += 30.0f * dt; // Herkes dönsün (gözlem için)
		}
	}
}