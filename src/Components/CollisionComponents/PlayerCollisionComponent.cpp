



#include "Components/CollisionComponents/PlayerCollisionComponent.hpp"



namespace Asteroid
{


	PlayerCollisionComponent::PlayerCollisionComponent(EntityHandle l_ownerEntityHandle)
		:CollisionComponent(l_ownerEntityHandle)
	{

	}

	bool PlayerCollisionComponent::Update(UpdateComponents& l_updateContext)
	{
		return true;
	}

	void PlayerCollisionComponent::CollisionReaction(Entity& l_entityItCollidedWith, Entity& l_collisionReactContext)
	{

	}

}