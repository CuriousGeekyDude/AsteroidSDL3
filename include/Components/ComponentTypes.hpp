#pragma once



#include <cinttypes>


namespace Asteroid
{

	enum class ComponentTypes : uint32_t
	{
		INDEFINITE_ENTITY_ANIMATION,
		EXPLOSION_FIRE_ASTEROID_ANIMATION,
		WARP_ASTEROID_ANIMATION,

		INPUT,

		MOVEMENT,

		COLLISION,

		
		STATE,
		ACTIVE_BASED_STATE,

	};

}