#pragma once




#include "Components/GraphicsComponent.hpp"
#include <glm.hpp>


struct SDL_Texture;


namespace Asteroid
{
	class Entity;

	namespace RenderSystem
	{
		class Renderer;
	}

	class PlayerGraphicsComponent : public GraphicsComponent
	{
	
	public:

		PlayerGraphicsComponent( uint32_t l_textureHandle
								,RenderSystem::Renderer* l_renderer
		                        ,Entity* l_entity);

		bool Update(float l_lastFrameElapsedTime) override;



	};
}