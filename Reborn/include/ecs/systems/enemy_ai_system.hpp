#pragma once
#include "spriteset.hpp"

namespace ecs
{
	struct EnemyAISystem
	{
		float enemySpeed = 160.0f;
		float facingOffsetDeg = 0.0f;

		void update(SpriteSet& S, int playerIndex, float dt);
	};
}
