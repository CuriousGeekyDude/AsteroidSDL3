#pragma once



#include <cinttypes>


namespace Asteroid
{

	enum class ComponentTypes : uint8_t
	{
		GRAPHICS,
		INPUT,
		MOVEMENT,
		COLLISION,
		STATE
	};

}