#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <cstdlib>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "vendor/glm/glm.hpp"
#include "vendor/glm/gtc/matrix_transform.hpp"
#include "vendor/glm/gtc/type_ptr.hpp"


//#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image/stb_image.h"

//static constexpr float kBulletFacingOffsetDeg = 90.0f;
//
//static constexpr float kMuzzleForward = 20.0f;
//static constexpr float kMuzzleRight = -55.0f;
//
//enum EntityType : uint8_t { ET_None = 0, ET_Player = 1, ET_Enemy = 2, ET_Bullet = 3 };

//static GLuint compileShader(GLenum type, const char* src)
//{
//	GLuint s = glCreateShader(type);
//	glShaderSource(s, 1, &src, nullptr);
//	glCompileShader(s);
//	GLint ok = 0;
//	glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
//	if (!ok)
//	{
//		char log[2048];
//		glGetShaderInfoLog(s, 2048, nullptr, log);
//		std::cerr << "Shader compile error \n" << log << std::endl;
//	}
//	return s;
//}
//
//static GLuint linkProgram(GLuint vs, GLuint fs)
//{
//	GLuint p = glCreateProgram();
//	glAttachShader(p, vs);
//	glAttachShader(p, fs);
//	glLinkProgram(p);
//	GLint ok = 0;
//	glGetProgramiv(p, GL_LINK_STATUS, &ok);
//	if (!ok)
//	{
//		char log[2048];
//		glGetProgramInfoLog(p, 2048, nullptr, log);
//		std::cerr << "Program link error \n" << log << std::endl;
//	}
//
//	glDetachShader(p, vs);
//	glDetachShader(p, fs);
//	glDeleteShader(vs);
//	glDeleteShader(fs);
//	return p;
//}




//struct Texture2D
//{
//	GLuint id = 0;
//	int width = 0, height = 0, channels = 0;
//
//	bool LoadFromFile(const std::string& path, bool flipY = true)
//	{
//		if (flipY) stbi_set_flip_vertically_on_load(true);
//		unsigned char* pixels = stbi_load(path.c_str(), &width, &height, &channels, 4);
//
//		if (!pixels)
//		{
//			std::cerr << "stb_image couldnt load " << path << std::endl;
//			return false;
//		}
//
//		if (id == 0) glGenTextures(1, &id);
//		glBindTexture(GL_TEXTURE_2D, id);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
//		glGenerateMipmap(GL_TEXTURE_2D);
//		glBindTexture(GL_TEXTURE_2D, 0);
//		stbi_image_free(pixels);
//		return true;
//	}
//
//	void Bind(int unit = 0) const {
//		glActiveTexture(GL_TEXTURE0 + unit);
//		glBindTexture(GL_TEXTURE_2D, id);
//	}
//};

// sprite cizmek icin tek bir orta quad (vao/vbo/ebo)
// pozisyon: merkezli -0.5..0.5, uv: 0..1

struct QuadMesh
{
	GLuint vao = 0, vbo = 0, ebo = 0;
	void Create()
	{
		if (vao) return;

		float verts[] = {
			// x, y,         u, v
			-0.5f, -0.5f,   0.0f, 0.0f, // 0
			0.5f, -0.5f,    1.0f, 0.0f, // 1
			0.5f, 0.5f,     1.0f, 1.0f, // 2
			-0.5f, 0.5f,    0.0f, 1.0f  // 3
		};

		unsigned int idx[] = { 0, 1, 2,   2, 3, 0 };

		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(idx), idx, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

		glBindVertexArray(0);
	}

	void Draw() const
	{
		glBindVertexArray(vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
} gQuad;

//static const char* kSpriteVS = R"(#version 330 core
//layout(location=0) in vec2 aPos;
//layout(location=1) in vec2 aUV;
//out vec2 vUV;
//uniform mat4 uMVP;
//void main(){
//    vUV = aUV;
//    gl_Position = uMVP * vec4(aPos.xy, 0.0, 1.0);
//}
//)";
//
//static const char* kSpriteFS = R"(#version 330 core
//in vec2 vUV;
//out vec4 FragColor;
//uniform sampler2D uTex;
//uniform vec4 uTint;
//void main(){
//    // Doku * renk çarpýmý. Alpha blending açýk.
//    FragColor = texture(uTex, vUV) * uTint;
//}
//)";

//struct SpriteRenderer
//{
//	GLuint program = 0;
//	GLint loc_uMVP = -1, loc_uTex = -1, loc_uTint = -1;
//
//	void Create()
//	{
//		if (program) return;
//
//		GLuint vs = compileShader(GL_VERTEX_SHADER, kSpriteVS);
//		GLuint fs = compileShader(GL_FRAGMENT_SHADER, kSpriteFS);
//
//		program = linkProgram(vs, fs);
//
//		loc_uMVP = glGetUniformLocation(program, "uMVP");
//		loc_uTex = glGetUniformLocation(program, "uTex");
//		loc_uTint = glGetUniformLocation(program, "uTint");
//	}
//} gRenderer;


struct SpriteSet
{
	// SoA diziler
	std::vector<const Texture2D*> tex;
	std::vector<glm::vec2> pos;
	std::vector<glm::vec2> size;
	std::vector<float> rotDeg;
	std::vector<glm::vec2> origin;
	std::vector<glm::vec4> tint;
	std::vector<glm::vec2> vel;
	std::vector<uint8_t> alive;

	// <0 ise sonsuz yasar
	std::vector<float> lifetime;
	std::vector<uint8_t> type;

	std::vector<int> freeIndices;  // to reuse the killed indices

	bool isPlayerDead;

	// entity olsutrma, entity = index
	int add(const Texture2D* t, glm::vec2 p, glm::vec2 s, float r = 0.f, glm::vec2 o = { 0.5f, 0.5f },
		glm::vec4 c = { 1, 1, 1, 1 }, glm::vec2 v = { 0, 0 }, float life = -1.0f, uint8_t et = ET_None)
	{
		int i;

		if (!freeIndices.empty())
		{
			// that means we can use one of free ind

			i = freeIndices.back();
			freeIndices.pop_back();

			tex[i] = t;
			pos[i] = p;
			size[i] = s;
			rotDeg[i] = r;
			origin[i] = o;
			tint[i] = c;
			vel[i] = v;
			alive[i] = 1;
			lifetime[i] = life;
			type[i] = et;
		}
		else
		{
			// or we will create new one

			i = (int)pos.size();
			tex.push_back(t);
			pos.push_back(p);
			size.push_back(s);
			rotDeg.push_back(r);
			origin.push_back(o);
			tint.push_back(c);
			vel.push_back(v);
			alive.push_back(1);
			lifetime.push_back(life);
			type.push_back(et);
		}

		return i;
	}
	int count() const { return (int)pos.size(); }

	// pratik spawn yardimcilari
	int spawnProjectile(const Texture2D* t, glm::vec2 p, glm::vec2 v, glm::vec2 s = { 8, 16 }, float life = 2.0f)
	{
		return add(t, p, s, 0.f, { 0.5f, 0.5f }, { 1, 1, 1, 1 }, v, life, ET_Bullet);
	}

	int spawnEnemy(const Texture2D* t, glm::vec2 p, glm::vec2 v, glm::vec2 s = { 48, 48 }, float life = -1.0f)
	{
		return add(t, p, s, 0.f, { 0.5f, 0.5f }, { 1, 1, 1, 1 }, v, life, ET_Enemy);
	}

	void kill(int i)
	{
		if (alive[i])
		{
			alive[i] = 0;
			freeIndices.push_back(i);
		}
	}

	void killThePlayer(int i)
	{
		kill(i);
		isPlayerDead = true;
	}
};

//static inline glm::vec2 getCenter(const SpriteSet& S, int i)
//{
//	return S.pos[i] + (glm::vec2{ 0.5f, 0.5f } - S.origin[i]) * S.size[i];
//}
//
//static inline float getRadius(const SpriteSet& S, int i)
//{
//	return 0.5f * std::min(S.size[i].x, S.size[i].y);
//}
//
//static inline float AngleDegFromVelocity(const glm::vec2& v)
//{
//	if (v.x == 0.0f && v.y == 0.0f) return 0.0f;
//	return glm::degrees(std::atan2(v.y, v.x));
//}

struct MouseLookSystem
{
	// sprite in default yonune gore duzeltme
	float facingOffsetDeg = -90.0f;

	void update(SpriteSet& S, GLFWwindow* win, int playerIndex, float zoom, int windowW, int windowH)
	{
		if (S.isPlayerDead) return;
		if (playerIndex < 0 || playerIndex >= S.count()) return;
		if (S.type[playerIndex] != ET_Player) return;

		double mx, my;
		glfwGetCursorPos(win, &mx, &my);

		float worldX = (float)mx * zoom;
		float worldY = ((float)windowH - (float)my) * zoom;

		glm::vec2 pc = getCenter(S, playerIndex);
		glm::vec2 dir = glm::vec2(worldX, worldY) - pc;

		if (dir.x == 0.0f && dir.y == 0.0f) return;

		float angleRad = std::atan2(dir.y, dir.x);
		float angleDeg = glm::degrees(angleRad) + facingOffsetDeg;

		S.rotDeg[playerIndex] = angleDeg;
	}
};

struct KeyEdge
{
	int key;
	bool isMouse;
	bool prevDown = false;
	KeyEdge(int k, bool mouse = false) : key(k), isMouse(mouse) {}
	bool pressed(GLFWwindow* w)
	{
		bool down = false;
		if (isMouse)
			down = glfwGetMouseButton(w, key) == GLFW_PRESS;
		else
			down = glfwGetKey(w, key) == GLFW_PRESS;

		bool rising = down && !prevDown;
		prevDown = down;
		return rising;
	}
};

struct InputSystem
{
	int controlledIndex = -1;

	KeyEdge fireKey{ GLFW_MOUSE_BUTTON_1, true };
	KeyEdge enemyKey{ GLFW_KEY_E };

	void update(SpriteSet& S, GLFWwindow* win, float dt, const Texture2D* bulletTex, const Texture2D* enemyTex, int worldW, int worldH, int zoom, int windowW, int windowH)
	{
		if (controlledIndex >= 0 && !S.isPlayerDead)
		{
			const float speed = 10.0f;
			const float deltaMult = 100000.0f;
			glm::vec2 d(0.0f);
			if (glfwGetKey(win, GLFW_KEY_A) == GLFW_PRESS) d.x -= 1;
			if (glfwGetKey(win, GLFW_KEY_D) == GLFW_PRESS) d.x += 1;
			if (glfwGetKey(win, GLFW_KEY_S) == GLFW_PRESS) d.y -= 1;
			if (glfwGetKey(win, GLFW_KEY_W) == GLFW_PRESS) d.y += 1;

			if (d.x != 0 || d.y != 0) d = glm::normalize(d);

			// DOD’de input sadece veriyi yazar; hareketi Movement yapar.
			S.vel[controlledIndex] = d * speed * dt * deltaMult;

		}

		// spawn projectile
		if (fireKey.pressed(win) && !S.isPlayerDead)
		{
			double mx, my;
			glfwGetCursorPos(win, &mx, &my);
			float worldX = (float)mx * zoom;
			float worldY = ((float)windowH - (float)my) * zoom;

			glm::vec2 pc = getCenter(S, controlledIndex);
			glm::vec2 dir = glm::vec2(worldX, worldY) - pc;
			float len = glm::length(dir);
			if (len < .3f) return;
			dir /= len;

			glm::vec2 right = glm::vec2(-dir.y, dir.x);

			float playerR = getRadius(S, controlledIndex);
			float bulletR = 8.0f;

			glm::vec2 spawnPos = pc + (dir * (playerR + bulletR + 2.0f + kMuzzleForward)) + (right * kMuzzleRight);

			float bulletSpeed = 1300.0f;
			glm::vec2 v = dir * bulletSpeed;

			glm::vec2 bulletSize = { 24, 48 };

			int bi = S.spawnProjectile(bulletTex, spawnPos, v, bulletSize, 2.0f);

			S.rotDeg[bi] = AngleDegFromVelocity(v) + kBulletFacingOffsetDeg;
		}

		// spawn enemy
		if (enemyKey.pressed(win))
		{
			float x = (float)(rand() % worldW);
			float y = (float)(rand() % worldH);
			glm::vec2 p = { x, y };
			glm::vec2 v = { 0.f, 0.f };
			S.spawnEnemy(enemyTex, p, v, { 120, 120 }, -1.0f);
		}
	}
};

struct LifeTimeSystem
{
	void update(SpriteSet& S, float dt)
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
};

struct MovementSystem {
	// Cache-dostu, dallanmasýz (alive kontrolü hariç) bir sýcak döngü.
	void update(SpriteSet& S, float dt) {
		const int N = S.count();
		for (int i = 0; i < N; ++i) {
			if (!S.alive[i]) continue; // Ölüyü atla. (Daha da iyisi: compact etmek.)
			S.pos[i] += S.vel[i] * dt;

			// Ýstersen ucuz bir davranýþ:
			 //S.rotDeg[i] += 30.0f * dt; // Herkes dönsün (gözlem için)
		}
	}
};

struct CollisionSystem
{
	std::vector<int> bullets, enemies;
	std::vector<glm::vec2> bulletCenters, enemyCenters;
	std::vector<float>     bulletRadii, enemyRadii;

	void update(SpriteSet& S, int controlledIndex)
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
			if (S.type[i] == ET_Bullet) bullets.push_back(i);
			else if (S.type[i] == ET_Enemy) enemies.push_back(i);
		}


		if (!S.isPlayerDead)
		{
			if (controlledIndex >= 0 && S.alive[controlledIndex]) {
				const glm::vec2 cP = getCenter(S, controlledIndex);
				const float     rP = getRadius(S, controlledIndex);
				for (int ei : enemies) {
					if (!S.alive[ei]) continue;
					const glm::vec2 cE = getCenter(S, ei);
					const float     rE = getRadius(S, ei);
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
			bulletCenters[b] = getCenter(S, bi);
			bulletRadii[b] = getRadius(S, bi);
		}

		enemyCenters.resize(enemies.size());
		enemyRadii.resize(enemies.size());
		for (size_t e = 0; e < enemies.size(); ++e) {
			int ei = enemies[e];
			enemyCenters[e] = getCenter(S, ei);
			enemyRadii[e] = getRadius(S, ei);
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

	static inline bool colliding(const glm::vec2& center1, const glm::vec2& center2, float radius1, float radius2)
	{
		glm::vec2 d = center1 - center2;
		float rsum = radius1 + radius2;

		return (glm::dot(d, d) <= rsum * rsum);
	}
};

struct EnemyAISystem
{
	float enemySpeed = 160.0f;
	float facingOffsetDeg = 0.0f;

	void update(SpriteSet& S, int playerIndex, float dt)
	{
		if (playerIndex < 0 || S.isPlayerDead || !S.alive[playerIndex]) return;

		const glm::vec2 pc = getCenter(S, playerIndex);
		const int N = S.count();

		for (int i = 0; i < N; ++i)
		{
			if (!S.alive[i] || S.type[i] != ET_Enemy) continue;

			glm::vec2 ec = getCenter(S, i);
			glm::vec2 dir = pc - ec;
			float len2 = glm::dot(dir, dir);

			if (len2 > 0.0f)
			{
				dir *= 1.0f / std::sqrt(len2); // normalize
				S.vel[i] = dir * enemySpeed;
				S.rotDeg[i] = glm::degrees(std::atan2(dir.y, dir.x)) + facingOffsetDeg;
			}
			else
			{
				S.vel[i] = { 0,0 };
			}
		}
	}
};

struct RenderSystem
{
	// Basit batching: texture id deðiþtikçe bind et.
	// (Bir sonraki adým: indeksleri texture’a göre gruplayýp tek seferde çizmek,
	//  daha sonraki adým: instancing / UBO / SSBO.)

	void draw(const SpriteSet& S, const glm::mat4& proj)
	{
		glUseProgram(gRenderer.program);
		glUniform1i(gRenderer.loc_uTex, 0);

		GLuint currentTex = 0;
		const int N = S.count();
		for (int i = 0; i < N; i++)
		{
			if (!S.alive[i]) continue;

			const Texture2D* t = S.tex[i];
			assert(t && t->id);

			if (t->id != currentTex) // Texture degistiyse sadece o an bind et
			{
				t->Bind(0);
				currentTex = t->id;
			}

			// Pivotu pixel cinsinden hesapla (origin 0..1 => size ile carp)
			//glm::vec2 pivot = { S.origin[i].x * S.size[i].x, S.origin[i].y * S.size[i].y };
			glm::vec2 pivot = (S.origin[i] - glm::vec2(0.5f, 0.5f)) * S.size[i];

			// model matrisi: T(poz) * T(pivot) * R * T(-pivot) * S(size)
			glm::mat4 model(1.0f);
			model = glm::translate(model, glm::vec3(S.pos[i], 0.0f));
			model = glm::translate(model, glm::vec3(pivot, 0.0f));
			model = glm::rotate(model, glm::radians(S.rotDeg[i]), glm::vec3(0, 0, 1));
			model = glm::translate(model, glm::vec3(-pivot, 0.0f));
			model = glm::scale(model, glm::vec3(S.size[i], 1.0f));

			glm::mat4 mvp = proj * model;

			// Uniformlari yaz ve quad i ciz
			glUniformMatrix4fv(gRenderer.loc_uMVP, 1, GL_FALSE, glm::value_ptr(mvp));
			glUniform4fv(gRenderer.loc_uTint, 1, glm::value_ptr(S.tint[i]));
			gQuad.Draw();
		}
	}
};

// - DOD akisi: Input -> Movement -> (diger sistemler) -> Render
// - Veriyi merkezde "SpriteSet" tutuyoruz. Sistemler sirayla dosdogru diziler uzerinde calisiyor

int main()
{
	double fpsTimeAcc = 0.0;
	int    fpsFrames = 0;
	char   titleBuf[128];

	// ---Pencere/GL baglami
	if (!glfwInit()) { std::cerr << "GLFW init failed\n"; return -1; }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	const int W = 1920;
	const int H = 1080;
	GLFWwindow* win = glfwCreateWindow(W, H, "Sprite DOD Starter", nullptr, nullptr);
	if (!win) { std::cerr << "Window creation failed\n"; glfwTerminate(); return -1; }
	glfwMakeContextCurrent(win);

	glfwSwapInterval(0); // vsync

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) { std::cerr << "GLEW init failed\n"; return -1; }

	glViewport(0, 0, W, H);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	gQuad.Create();
	gRenderer.Create();

	Texture2D texPlayer, texBullet, texEnemy;
	if (!texPlayer.LoadFromFile("assets/player.png")) { std::cerr << "player tex couldnt found\n"; return -1; }
	if (!texBullet.LoadFromFile("assets/bullet.png")) { std::cerr << "bullet tex couldnt found\n"; return -1; }
	if (!texEnemy.LoadFromFile("assets/enemy.png")) { std::cerr << "enemy tex couldnt found\n"; return -1; }

	// piksel uzayi ortografik projeksiyon (0..W 0..H)

	float zoom = 2.0f;
	glm::mat4 proj = glm::ortho(0.0f, (float)W * zoom, 0.0f, (float)H * zoom, -1.0f, 1.0f);

	SpriteSet S;

	// oyuncu entitysi "entity = index"
	S.isPlayerDead = false;
	int playerIndex = S.add(&texPlayer,
		{ W * 0.5f * zoom, H * 0.5f * zoom },    // pos
		{ (float)texPlayer.width, (float)texPlayer.height },  // size
		0.0f,     // rot
		{ 0.5f, 0.5f },    // pivot
		{ 1,1,1,1 },   // tint
		{ 0,0 }, -1.0f, ET_Player);    // vel

	//// (Ýstersen performans farkýný görmek için birçok sprite ekleyebilirsin)
	// for (int i=0; i<10; ++i) {
	//     float x = (float)(rand() % W);
	//     float y = (float)(rand() % H);
	//     S.add(&texHero, {x,y}, {(float)texHero.width*0.5f, (float)texHero.height*0.5f});
	// }

	// Sistemler
	InputSystem input;
	input.controlledIndex = playerIndex;
	MovementSystem movement;
	LifeTimeSystem lifeTime;
	RenderSystem render;
	CollisionSystem collision;
	MouseLookSystem mouseLook;
	EnemyAISystem enemyAI;

	mouseLook.facingOffsetDeg = 0.0f;

	enemyAI.enemySpeed = 160.0f;
	enemyAI.facingOffsetDeg = 90.0f;

	double last = glfwGetTime();
	while (!glfwWindowShouldClose(win))
	{
		glfwPollEvents();
		double now = glfwGetTime();
		float dt = float(now - last);
		last = now;


		fpsTimeAcc += dt;
		fpsFrames += 1;

		if (fpsTimeAcc >= 0.5) { // 0.5 sn’de bir güncelle
			double fps = fpsFrames / fpsTimeAcc;
			snprintf(titleBuf, sizeof(titleBuf), "Sprite DOD Starter  |  FPS: %.1f  |  dt: %.3f ms",
				fps, 1000.0 * (fpsTimeAcc / fpsFrames));
			glfwSetWindowTitle(win, titleBuf);
			fpsTimeAcc = 0.0;
			fpsFrames = 0;
		}


		mouseLook.update(S, win, playerIndex, zoom, W, H);
		// Input: yalnizca kontrol edilen enetitynin hizini gunceller
		input.update(S, win, dt, &texBullet, &texEnemy, (int)(W * zoom), (int)(H * zoom), zoom, W, H);

		enemyAI.update(S, playerIndex, dt);

		// Movement : butun alive entitylerde pos += vel*dt yapar.
		movement.update(S, dt);
		lifeTime.update(S, dt);
		collision.update(S, playerIndex);

		// gelecekte collisionSystem, lifetime system gibi seyler eklenebilir
		// Render: veriye bakip cize

		glClearColor(0.1f, 0.1f, 0.12f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		render.draw(S, proj);

		glfwSwapBuffers(win);
	}

	glfwDestroyWindow(win);
	glfwTerminate();
	return 0;
}


