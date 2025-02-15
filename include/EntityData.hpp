#pragma once



#include <glm.hpp>
#include <limits>



namespace Asteroid
{
	struct EntityData
	{
		bool m_hasPhysics{ true };
		bool m_isPlayer{ false };
		glm::vec2 m_pos{std::numeric_limits<float>::max()};
	};
}