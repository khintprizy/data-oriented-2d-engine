#pragma once
#include "spriteset.hpp"

namespace ecs
{
	struct LifeTimeSystem
	{
		void update(SpriteSet& S, float dt);
	};
}