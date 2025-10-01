#include <systems/render_system.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cassert>

namespace core
{
	void RenderSystem::draw(const ecs::SpriteSet& S, const RenderContext& ctx)
	{
		ctx.renderer.use();
		glUniform1i(ctx.renderer.loc_uTex, 0);

		GLuint currentTex = 0;
		const int N = S.count();

        for (int i = 0; i < N; ++i) {
            if (!S.alive[i]) continue;
            const auto* t = S.tex[i]; assert(t && t->id);
            if (t->id != currentTex) { t->bind(0); currentTex = t->id; }

            glm::vec2 pivot = (S.origin[i] - glm::vec2(0.5f, 0.5f)) * S.size[i];

            glm::mat4 model(1.f);
            model = glm::translate(model, glm::vec3(S.pos[i], 0.0f));
            model = glm::translate(model, glm::vec3(pivot, 0.0f));
            model = glm::rotate(model, glm::radians(S.rotDeg[i]), glm::vec3(0, 0, 1));
            model = glm::translate(model, glm::vec3(-pivot, 0.0f));
            model = glm::scale(model, glm::vec3(S.size[i], 1.0f));

            glm::mat4 mvp = ctx.projection * model;
            glUniformMatrix4fv(ctx.renderer.loc_uMVP, 1, GL_FALSE, glm::value_ptr(mvp));
            glUniform4fv(ctx.renderer.loc_uTint, 1, glm::value_ptr(S.tint[i]));
            ctx.quad.draw();
        }
	}
}