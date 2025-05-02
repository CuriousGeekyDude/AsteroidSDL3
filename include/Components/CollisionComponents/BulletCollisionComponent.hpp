#pragma once






#include "Components/CollisionComponent.hpp"



namespace Asteroid
{
	class RayMovementComponent;

	class BulletCollisionComponent : public CollisionComponent
	{
	public:

		BulletCollisionComponent(EntityHandle l_ownerEntityHandle, const RayMovementComponent* l_ownerMovComponent, DelayDeactiveBasedStateComponent* l_delayedDeactiveComponent);

		bool Update(UpdateComponents& l_updateContext) override;

		void CollisionReaction(Entity& l_entityItCollidedWith, CollisionReactionContext& l_collisionReactContext) override;

	private:

		const RayMovementComponent* m_ownerMovComponent{};


	};

}