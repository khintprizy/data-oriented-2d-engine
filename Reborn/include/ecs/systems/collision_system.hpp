#pragma once
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "spriteset.hpp"

namespace ecs
{
	struct CollisionSystem
	{
		std::vector<int> bullets, enemies;
		std::vector<glm::vec2> bulletCenters, enemyCenters;
		std::vector<float> bulletRadii, enemyRadii;

		void update(SpriteSet& S, int controlledIndex);
		bool colliding(const glm::vec2& center1, const glm::vec2 center2, float radius1, float radius2);
	};
}