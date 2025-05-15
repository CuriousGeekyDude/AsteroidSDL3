#pragma once




#include <glm.hpp>



namespace Asteroid
{


	struct MovementMetaData final
	{
		glm::vec2 m_speed;
		glm::vec2 m_initialPos{};
		glm::vec2 m_rayDirection{};
		float m_initialT{};
		float m_thetaDegrees{};
		bool m_pauseMovement;
		
	};

}