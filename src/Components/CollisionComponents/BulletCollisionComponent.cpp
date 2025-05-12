





#include "Components/CollisionComponents/BulletCollisionComponent.hpp"
#include "Entities/Entity.hpp"
#include "Components/StateComponents/ActiveBasedStateComponent.hpp"
#include "Systems/CallbacksTimer.hpp"
#include "Systems/LogSystem.hpp"

namespace Asteroid
{

	
	BulletCollisionComponent::BulletCollisionComponent()
	{

	}

	bool BulletCollisionComponent::Update(UpdateComponents& l_updateContext)
	{
		return true;
	}



	void BulletCollisionComponent::Init(EntityHandle l_ownerEntityHandle
		, const uint32_t l_frameCountToActivateCollision
		, const uint32_t l_frameCountToDeactivateCollision
		, const bool l_isCollisionActive
		, IndefiniteRepeatableAnimationComponent* l_repeatableAnimComponent
		, const ActiveBasedStateComponent* l_activeComponent)
	{
		CollisionComponent::Init(l_ownerEntityHandle, l_frameCountToActivateCollision, l_frameCountToDeactivateCollision, l_isCollisionActive, l_repeatableAnimComponent);
		m_activeComponent = l_activeComponent;
	}


	void BulletCollisionComponent::CollisionReaction(Entity& l_entityItCollidedWith, Entity& l_ownerEntity, CallbacksTimer& l_callBackTimes)
	{

		using namespace LogSystem;

		if (EntityType::BULLET == l_entityItCollidedWith.GetType() || EntityType::PLAYER == l_entityItCollidedWith.GetType()) {
			return;
		}

		if (true == m_resetCollision) {
			m_firstCollision = true;
			m_resetCollision = false;
		}


		if (false == m_resetCollision && true == m_firstCollision && true == m_isCollisionActive) {

			l_ownerEntity.SetActiveState(false);

			m_firstCollision = false;

		}

	}

}