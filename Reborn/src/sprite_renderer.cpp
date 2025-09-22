#include "sprite_renderer.hpp"
#include "gl_utils.hpp"
#include <glm/gtc/type_ptr.hpp>

namespace
{
	const char* kSpriteVS = R"(#version 330 core
    layout(location=0) in vec2 aPos;
    layout(location=1) in vec2 aUV;
    out vec2 vUV;
    uniform mat4 uMVP;
    void main(){
    vUV = aUV;
    gl_Position = uMVP * vec4(aPos.xy, 0.0, 1.0);
    }
    )";

	const char* kSpriteFS = R"(#version 330 core
    in vec2 vUV;
    out vec4 FragColor;
    uniform sampler2D uTex;
    uniform vec4 uTint;
    oid main(){
    // Doku * renk çarpýmý. Alpha blending açýk.
    FragColor = texture(uTex, vUV) * uTint;
    }
    )";
}

namespace core
{
    void SpriteRenderer::create() {
        if (program) return;
        GLuint vs = compileShader(GL_VERTEX_SHADER, kSpriteVS);
        GLuint fs = compileShader(GL_FRAGMENT_SHADER, kSpriteFS);
        program = linkProgram(vs, fs);
        loc_uMVP = glGetUniformLocation(program, "uMVP");
        loc_uTex = glGetUniformLocation(program, "uTex");
        loc_uTint = glGetUniformLocation(program, "uTint");
    }
    void SpriteRenderer::use() const { glUseProgram(program); }
}