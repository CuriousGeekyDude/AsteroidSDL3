#pragma once





#include "Systems/TimeRewind/EntityFrameTimeRewind.hpp"
#include <array>



namespace Asteroid
{

	struct Frame final
	{
		//193 is the total number of entities we always initialize 
		std::array<EntityFrameTimeRewind, 193U> m_allEntitysMetaDataInThisFrame{};
		glm::vec2 m_mousePos{};
		float m_time{};
		uint32_t m_totalNumBulletsHitAsteroid{};
		bool m_isMouseHidden{};

	};

}