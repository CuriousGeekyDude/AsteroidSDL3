




#include "Components/CollisionComponent.hpp"



namespace Asteroid
{


	CollisionComponent::CollisionComponent()
	{

	}


	void CollisionComponent::SetCollisionState(const bool l_collisionState)
	{
		m_isCollisionActive = l_collisionState;
	}


	void CollisionComponent::Reset()
	{
		m_resetCollision = true;
		m_firstCollision = false;
	}


	bool CollisionComponent::IsCollisionReset() const
	{
		return m_resetCollision;
	}
	bool CollisionComponent::IsFirstCollision() const
	{
		return m_firstCollision;
	}

	void CollisionComponent::Init(EntityHandle l_ownerEntityHandle
		, const uint32_t l_frameCountToActivateCollision
		, const uint32_t l_frameCountToDeactivateCollision
		, const bool l_isCollisionActive
		, IndefiniteRepeatableAnimationComponent* l_repeatableAnimComponent)
	{
		Component::Init(l_ownerEntityHandle);


		m_frameCountToActivateCollision = l_frameCountToActivateCollision;
		m_frameCountToDeactivateCollision = l_frameCountToDeactivateCollision;
		m_isCollisionActive = l_isCollisionActive;
		m_repeatableAnimationComponent = l_repeatableAnimComponent;

	}



	bool CollisionComponent::GetCollisionState() const
	{
		return m_isCollisionActive;
	}



	void CollisionComponent::SetCollisionResetFlag(const bool l_resetCollision)
	{
		m_resetCollision = l_resetCollision;
	}
	void CollisionComponent::SetCollisionFirstFlag(const bool l_collisionFirst)
	{
		m_firstCollision = l_collisionFirst;
	}


	uint32_t CollisionComponent::GetFrameCountToActivateCollision() const
	{
		return m_frameCountToActivateCollision;
	}
	uint32_t CollisionComponent::GetFrameCountToDeactivateCollision() const
	{
		return m_frameCountToDeactivateCollision;
	}

}