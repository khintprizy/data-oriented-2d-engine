#pragma once
#include "spriteset.hpp"

namespace ecs
{
	struct MovementSystem
	{
		void update(SpriteSet& S, float dt);
	};
}