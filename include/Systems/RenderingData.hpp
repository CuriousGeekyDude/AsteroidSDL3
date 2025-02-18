#pragma once



#include <glm.hpp>


struct SDL_Texture;

namespace Asteroid
{

	namespace RenderSystem
	{
		struct RenderingData
		{
			glm::vec2 m_entityPos{};
			SDL_Texture* m_entityTexture{};
		};
	}

}