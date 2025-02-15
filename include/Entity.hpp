#pragma once




#include "EntityData.hpp"


namespace Asteroid
{
	struct Entity
	{

		explicit Entity(const EntityData& l_initialData);


		EntityData m_data;
		
	};
}