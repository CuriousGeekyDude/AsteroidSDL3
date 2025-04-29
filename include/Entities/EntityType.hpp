#pragma once



#include <stdint.h>


namespace Asteroid
{
	enum class EntityType : uint32_t
	{
		PLAYER = 0,
		BULLET,
		ASTEROID
	};
}