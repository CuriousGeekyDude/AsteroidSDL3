#pragma once






#include "Components/CollisionComponent.hpp"



namespace Asteroid
{
	class RayMovementComponent;

	class BulletCollisionComponent : public CollisionComponent
	{
	public:

		BulletCollisionComponent(EntityHandle l_ownerEntityHandle);

		bool Update(UpdateComponents& l_updateContext) override;

		void CollisionReaction(Entity& l_entityItCollidedWith, Entity& l_ownerEntity) override;

	private:

	};

}