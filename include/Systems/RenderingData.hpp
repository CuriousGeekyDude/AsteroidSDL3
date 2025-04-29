#pragma once



#include <glm.hpp>


namespace Asteroid
{

	namespace RenderSystem
	{
		struct RenderingData
		{
			glm::vec2 m_entityPos{};
			glm::vec2 m_centerOfRotation{};
			uint32_t m_entityTextureHandle{};
			int m_widthToRender;
			int m_heightToRender;
			float m_angleOfRotation;
		};
	}

}