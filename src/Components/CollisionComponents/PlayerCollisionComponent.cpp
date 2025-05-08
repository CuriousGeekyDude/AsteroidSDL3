



#include "Components/CollisionComponents/PlayerCollisionComponent.hpp"



namespace Asteroid
{


	PlayerCollisionComponent::PlayerCollisionComponent()
	{

	}




	void PlayerCollisionComponent::Init(EntityHandle l_ownerEntityHandle
		, const uint32_t l_frameCountToActivateCollision
		, const uint32_t l_frameCountToDeactivateCollision
		, const bool l_isCollisionActive
		, IndefiniteRepeatableAnimationComponent* l_repeatableAnimComponent)
	{
		CollisionComponent::Init(l_ownerEntityHandle, l_frameCountToActivateCollision, l_frameCountToDeactivateCollision, l_isCollisionActive, l_repeatableAnimComponent);

	}

	bool PlayerCollisionComponent::Update(UpdateComponents& l_updateContext)
	{
		return true;
	}

	void PlayerCollisionComponent::CollisionReaction(Entity& l_entityItCollidedWith, Entity& l_collisionReactContext, CallbacksTimer& l_timer)
	{

	}

}