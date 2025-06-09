





#include "Components/CollisionComponents/AsteroidCollisionComponent.hpp"
#include "Components/OnceRepeatableAnimationComponent.hpp"
#include "Entities/Entity.hpp"
#include "Components/StateComponents/ActiveBasedStateComponent.hpp"
#include "Systems/CallbacksTimer.hpp"
#include "Systems/LogSystem.hpp"
#include "Components/UpdateComponents.hpp"
#include "Systems/EventSystem/IEventCollision.hpp"


namespace Asteroid
{

	AsteroidCollisionComponent::AsteroidCollisionComponent()
	{

	}




	void AsteroidCollisionComponent::Init(EntityHandle l_ownerEntityHandle
		, const uint32_t l_frameCountToActivateCollision
		, const uint32_t l_frameCountToDeactivateCollision
		, const bool l_isCollisionActive
		, IndefiniteRepeatableAnimationComponent* l_repeatableAnimComponent
		, OnceRepeatableAnimationComponent* l_fireExplosionAnimation
		, ActiveBasedStateComponent* l_activeComponent)
	{
		CollisionComponent::Init(l_ownerEntityHandle, l_frameCountToActivateCollision, l_frameCountToDeactivateCollision, l_isCollisionActive, l_repeatableAnimComponent);
		m_fireExplosionAnimation = l_fireExplosionAnimation;
		m_activeComponent = l_activeComponent;
	}



	bool AsteroidCollisionComponent::Update(UpdateComponents& l_updateContext)
	{
		l_updateContext.m_totalNumAsteroidsHitByBullets += m_hitBullet;
		m_hitBullet = 0U;
		return true;
	}




	uint32_t AsteroidCollisionComponent::IsHitByBullet() const
	{
		return m_hitBullet;
	}



	void AsteroidCollisionComponent::SetBulletHitFlag(const uint32_t l_hitBullet)
	{
		m_hitBullet = l_hitBullet;
	}

	void AsteroidCollisionComponent::CollisionReaction(IEvent* l_collisionEvent)
	{
		
		using namespace LogSystem;


		if (true == m_resetCollision) {
			m_firstCollision = true;
			m_resetCollision = false;
		}


		IEventCollision* lv_collisionEvent = static_cast<IEventCollision*>(l_collisionEvent);
		Entity* lv_entityItCollidedWith{};
		Entity* lv_ownerEntity{};

		if (lv_collisionEvent->GetEntity1()->GetID() == m_ownerEntityHandle.m_entityHandle) {
			lv_entityItCollidedWith = lv_collisionEvent->GetEntity1();
			lv_ownerEntity = lv_collisionEvent->GetEntity2();
		}
		else {
			lv_entityItCollidedWith = lv_collisionEvent->GetEntity2();
			lv_ownerEntity = lv_collisionEvent->GetEntity1();
		}


		if (false == m_resetCollision && true == m_firstCollision && true == m_isCollisionActive) {

			if (EntityType::BULLET == lv_entityItCollidedWith->GetType()) {
				++m_hitBullet;
			}
		
			m_fireExplosionAnimation->StartAnimation();
			bool lv_stateValue{ false };

			DelayedSetStateCallback lv_delayedDeactive
			{ .m_callback{[lv_ownerEntity, lv_stateValue] {lv_ownerEntity->SetActiveState(lv_stateValue); }},
			  .m_currentFrame = 0U,
			  .m_maxNumFrames = m_activeComponent->GetframeCountToDeactivate(),
			};

			lv_collisionEvent->m_callbackTimer->AddSetStateCallback(std::move(lv_delayedDeactive));

			m_activeComponent->SetDelayedActivationCallbackFlag(true);

			DelayedSetStateCallback lv_delayedCollisionDeactivate
			{
				.m_callback{[this, lv_stateValue] {this->SetCollisionState(lv_stateValue); }},
				.m_currentFrame = 0U,
				.m_maxNumFrames = m_frameCountToDeactivateCollision
			};
			lv_collisionEvent->m_callbackTimer->AddSetStateCallback(std::move(lv_delayedCollisionDeactivate));

			m_repeatableAnimationComponent->SetVisibleState(false);
			LOG(Severity::INFO, Channel::PROGRAM_LOGIC, "2 callbacks have been recorded for an asteroid entity.");
			m_firstCollision = false;

		}

	}

}