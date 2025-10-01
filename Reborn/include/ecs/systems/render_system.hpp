#pragma once
#include <glm/mat4x4.hpp>
#include <render_context.hpp>
#include <spriteset.hpp>

namespace core
{
	struct RenderSystem
	{
		void draw(const ecs::SpriteSet& S, const RenderContext& ctx);
	};
}