#pragma once




#include "Components/GraphicsComponent.hpp"



namespace Asteroid
{

	class RayMovementComponent;


	class BulletGraphicsComponent : public GraphicsComponent
	{


	public:

		BulletGraphicsComponent(uint32_t l_textureHandle, EntityHandle l_entityHandle
		, const RayMovementComponent* l_bulletMovementComponent);


		bool Update(UpdateComponents& l_updateContext) override;


	private:

		const RayMovementComponent* m_bulletMovementComponent;


	};
}