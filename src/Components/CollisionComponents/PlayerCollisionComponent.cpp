



#include "Components/CollisionComponents/PlayerCollisionComponent.hpp"



namespace Asteroid
{


	PlayerCollisionComponent::PlayerCollisionComponent(EntityHandle l_ownerEntityHandle, DelayDeactiveBasedStateComponent* l_delayedDeactiveComponent)
		:CollisionComponent(l_ownerEntityHandle, l_delayedDeactiveComponent)
	{

	}

	bool PlayerCollisionComponent::Update(UpdateComponents& l_updateContext)
	{
		return true;
	}

	void PlayerCollisionComponent::CollisionReaction(Entity& l_entityItCollidedWith, CollisionReactionContext& l_collisionReactContext)
	{

	}

}