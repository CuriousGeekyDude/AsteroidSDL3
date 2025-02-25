#pragma once




#include "Components/GraphicsComponent.hpp"
#include <glm.hpp>


struct SDL_Texture;


namespace Asteroid
{
	class MovementComponent;
	class Entity;

	namespace RenderSystem
	{
		class Renderer;
	}

	class PlayerGraphicsComponent : public GraphicsComponent
	{
	
	public:

		PlayerGraphicsComponent( uint32_t l_textureHandle
								,MovementComponent* l_movementComponent
								,RenderSystem::Renderer* l_renderer
		                        ,Entity* l_entity);

		bool Update(float l_lastFrameElapsedTime) override;


	protected:

		MovementComponent* m_movementComponent;

	};
}