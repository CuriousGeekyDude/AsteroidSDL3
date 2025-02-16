#pragma once



#include <glm.hpp>
#include <limits>



namespace Asteroid
{
	struct EntityData
	{
		bool m_hasPhysics{ true };
		bool m_isPlayer{ false };
		bool m_isVisible{ true };
		uint32_t m_textureHandle{std::numeric_limits<uint32_t>::max()};
		glm::vec2 m_pos{std::numeric_limits<float>::max()};

	};
}