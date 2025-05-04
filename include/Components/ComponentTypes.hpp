#pragma once



#include <cinttypes>


namespace Asteroid
{

	enum class ComponentTypes : uint32_t
	{
		GRAPHICS,
		EXPLOSION_FIRE_ASTEROID_ANIMATION,

		INPUT,

		MOVEMENT,

		COLLISION,

		
		STATE,
		ACTIVE_BASED_STATE,
		VISIBILITY_BASED_STATE,
		COLLISION_BASED_STATE



	};

}