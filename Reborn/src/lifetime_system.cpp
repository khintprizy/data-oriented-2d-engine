#include "systems/lifetime_system.hpp"

namespace ecs
{
	void LifeTimeSystem::update(SpriteSet& S, float dt)
	{
		const int N = S.count();
		for (int i = 0; i < N; ++i)
		{
			if (!S.alive[i]) continue;
			float& life = S.lifetime[i];
			if (life >= 0.0f)
			{
				life -= dt;
				if (life <= 0.0f)
				{
					S.kill(i);
				}
			}
		}
	}
}