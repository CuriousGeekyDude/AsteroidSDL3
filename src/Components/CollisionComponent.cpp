




#include "Components/CollisionComponent.hpp"



namespace Asteroid
{

	CollisionComponent::CollisionComponent(EntityHandle l_ownerEntityHandle, DelayDeactiveBasedStateComponent* l_delayedDeactiveComponent)
		:Component(l_ownerEntityHandle)
		,m_delayedDeactiveComponent(l_delayedDeactiveComponent)
	{

	}



	void CollisionComponent::ResetCollision()
	{
		m_resetCollision = true;
	}
}