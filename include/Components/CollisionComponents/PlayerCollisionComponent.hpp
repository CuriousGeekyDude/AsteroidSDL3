#pragma once






#include "Components/CollisionComponent.hpp"


namespace Asteroid
{

	class PlayerCollisionComponent : public CollisionComponent
	{
	public:

		PlayerCollisionComponent(EntityHandle l_ownerEntityHandle, DelayDeactiveBasedStateComponent* l_delayedDeactiveComponent);

		bool Update(UpdateComponents& l_updateContext) override;

		void CollisionReaction(Entity& l_entityItCollidedWith, CollisionReactionContext& l_collisionReactContext) override;

	};


}