#pragma once

#include <cstdint>

namespace core 
{
	inline constexpr float kBulletFacingOffsetDeg = 90.0f;

	inline constexpr float kMuzzleForward = 20.0f;
	inline constexpr float kMuzzleRight = -55.0f;

	enum EntityType : uint8_t { ET_None = 0, ET_Player = 1, ET_Enemy = 2, ET_Bullet = 3 };
}