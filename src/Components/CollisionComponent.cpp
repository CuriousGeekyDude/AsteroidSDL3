




#include "Components/CollisionComponent.hpp"



namespace Asteroid
{

	CollisionComponent::CollisionComponent(EntityHandle l_ownerEntityHandle)
		:Component(l_ownerEntityHandle)
	{

	}



	void CollisionComponent::ResetCollision()
	{
		m_resetCollision = true;
	}
}