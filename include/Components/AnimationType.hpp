#pragma once



#include <cinttypes>


namespace Asteroid
{
	enum class AnimationType : uint32_t
	{
		EXPLOSION_FIRE_ASTEROID = 0U,
		ASTEROID,
		MAIN_SPACESHIP,
		LASER_BEAM,

		INVALID
	};
}