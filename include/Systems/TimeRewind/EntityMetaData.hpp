#pragma once





#include <glm.hpp>
#include "Entities/EntityType.hpp"


namespace Asteroid
{

	struct EntityMetaData final
	{
		glm::vec2 m_pos{};
		uint32_t m_id{};
		EntityType m_type{};
		bool m_isActive{};
	};

}