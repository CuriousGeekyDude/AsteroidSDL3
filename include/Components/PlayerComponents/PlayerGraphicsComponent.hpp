#pragma once




#include "Components/GraphicsComponent.hpp"
#include <glm.hpp>


struct SDL_Texture;


namespace Asteroid
{

	class PlayerMovementComponent;

	class PlayerGraphicsComponent : public GraphicsComponent
	{
	
	public:

		PlayerGraphicsComponent(uint32_t l_textureHandle, EntityHandle l_entityHandle
			, const PlayerMovementComponent* l_playerMovementComponent);

		bool Update(UpdateComponents& l_updateContext) override;


	private:
		const PlayerMovementComponent* m_playerMovementComponent;
	};
}