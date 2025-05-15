#pragma once





#include <glm.hpp>



namespace Asteroid
{


	struct OnceRepeatAnimationMetaData final
	{

		glm::vec2 m_initialPos{};
		uint32_t m_currentOffset{};
		bool m_startAnimation{};

	};

}