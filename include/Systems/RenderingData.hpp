#pragma once



#include <glm.hpp>


namespace Asteroid
{

	namespace RenderSystem
	{
		struct RenderingData
		{
			glm::vec2 m_entityPos{};
			uint32_t m_entityTextureHandle{};
		};
	}

}