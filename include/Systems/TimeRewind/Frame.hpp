#pragma once





#include "Systems/TimeRewind/EntityFrameTimeRewind.hpp"
#include "Systems/DelayedSetStateCallback.hpp"
#include <array>
#include <vector>


namespace Asteroid
{

	struct Frame final
	{
		//194 is the total number of entities we always initialize 
		std::array<EntityFrameTimeRewind, 194U> m_allEntitysMetaDataInThisFrame{};
		std::vector<DelayedSetStateCallback> m_delayedCallbacks{};
		glm::vec2 m_mousePos{};
		float m_time{};
		uint32_t m_totalNumBulletsHitAsteroid{};
		bool m_isMouseHidden{};

	};

}