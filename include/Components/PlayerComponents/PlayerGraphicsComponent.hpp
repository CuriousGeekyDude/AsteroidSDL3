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

	class PlayerMovementComponent;

	class PlayerGraphicsComponent : public GraphicsComponent
	{
	
	public:

		PlayerGraphicsComponent( uint32_t l_textureHandle
								,RenderSystem::Renderer* l_renderer
		                        ,Entity* l_entity
								,const PlayerMovementComponent& l_playerMovementComponent);

		bool Update(float l_lastFrameElapsedTime) override;


	private:
		const PlayerMovementComponent* m_playerMovementComponent;
	};
}