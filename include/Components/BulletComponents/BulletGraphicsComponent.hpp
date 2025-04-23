#pragma once




#include "Components/GraphicsComponent.hpp"



namespace Asteroid
{

	class RayMovementComponent;


	class BulletGraphicsComponent : public GraphicsComponent
	{


	public:

		BulletGraphicsComponent(uint32_t l_textureHandle
			, RenderSystem::Renderer* l_renderer, EntityHandle l_entityHandle
		, const glm::ivec2& l_windowResolution, const RayMovementComponent* l_bulletMovementComponent
		, Engine* l_engine);


		bool Update(float l_deltaTime) override;

		


	private:

		const RayMovementComponent* m_bulletMovementComponent;


	};
}