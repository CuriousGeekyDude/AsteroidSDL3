





#include "Components/CollisionComponents/BulletCollisionComponent.hpp"
#include "Entities/Entity.hpp"
#include "Components/StateComponents/ActiveBasedStateComponent.hpp"
#include "Systems/CallbacksTimer.hpp"
#include "Systems/LogSystem.hpp"
#include "Systems/EventSystem/EventCollision.hpp"

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


	void BulletCollisionComponent::CollisionReaction(IEvent* l_collisionEvent)
	{

		using namespace LogSystem;


		EventCollision* lv_collisionEvent = static_cast<EventCollision*>(l_collisionEvent);
		Entity* lv_entityItCollidedWith{};
		Entity* lv_ownerEntity{};

		if (lv_collisionEvent->GetEntity1()->GetID() == m_ownerEntityHandle.m_entityHandle) {
			lv_entityItCollidedWith = lv_collisionEvent->GetEntity2();
			lv_ownerEntity = lv_collisionEvent->GetEntity1();
		}
		else {
			lv_entityItCollidedWith = lv_collisionEvent->GetEntity1();
			lv_ownerEntity = lv_collisionEvent->GetEntity2();
		}


		if (EntityType::BULLET == lv_entityItCollidedWith->GetType() || EntityType::PLAYER == lv_entityItCollidedWith->GetType()) {
			return;
		}

		if (true == m_resetCollision) {
			m_firstCollision = true;
			m_resetCollision = false;
		}


		if (false == m_resetCollision && true == m_firstCollision && true == m_isCollisionActive) {

			lv_ownerEntity->SetActiveState(false);

			m_firstCollision = false;

		}

	}

}