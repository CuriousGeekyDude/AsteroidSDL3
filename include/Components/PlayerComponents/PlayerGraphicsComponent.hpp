#pragma once




#include "Components/GraphicsComponent.hpp"
#include <glm.hpp>


struct SDL_Texture;


namespace Asteroid
{
	class PlayerMovementComponent;
	class Entity;

	namespace RenderSystem
	{
		class Renderer;
	}

	class PlayerGraphicsComponent : public GraphicsComponent
	{
	
	public:

		PlayerGraphicsComponent( uint32_t l_textureHandle
								, PlayerMovementComponent* l_movementComponent
								,RenderSystem::Renderer* l_renderer
		                        ,Entity* l_entity);

		bool Update(float l_lastFrameElapsedTime) override;


	protected:

		PlayerMovementComponent* m_movementComponent;

	};
}