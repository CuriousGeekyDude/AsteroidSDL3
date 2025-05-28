#pragma once



#include <cinttypes>
#include "Components/AttributeComponents/AsteroidStates.hpp"



namespace Asteroid
{

	struct AttributeMetaData final
	{

		uint32_t m_hp{};
		AsteroidStates m_asteroidStates{};

	};

}