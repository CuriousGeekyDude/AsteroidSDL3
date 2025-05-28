





#include "Components/CollisionComponents/AsteroidCollisionComponent.hpp"
#include "Components/OnceRepeatableAnimationComponent.hpp"
#include "Entities/Entity.hpp"
#include "Components/StateComponents/ActiveBasedStateComponent.hpp"
#include "Systems/CallbacksTimer.hpp"
#include "Systems/LogSystem.hpp"
#include "Components/UpdateComponents.hpp"


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

	void AsteroidCollisionComponent::CollisionReaction(Entity& l_entityItCollidedWith
		, Entity& l_ownerEntity, CallbacksTimer& l_timer)
	{
		
		using namespace LogSystem;


		if (true == m_resetCollision) {
			m_firstCollision = true;
			m_resetCollision = false;
		}



		if (false == m_resetCollision && true == m_firstCollision && true == m_isCollisionActive) {

			if (EntityType::BULLET == l_entityItCollidedWith.GetType()) {
				++m_hitBullet;
			}
		
			m_fireExplosionAnimation->StartAnimation();
			bool lv_stateValue{ false };

			DelayedSetStateCallback lv_delayedDeactive
			{ .m_callback{[&l_ownerEntity, lv_stateValue] {l_ownerEntity.SetActiveState(lv_stateValue); }},
			  .m_currentFrame = 0U,
			  .m_maxNumFrames = m_activeComponent->GetframeCountToDeactivate(),
			};

			l_timer.AddSetStateCallback(std::move(lv_delayedDeactive));

			m_activeComponent->SetDelayedActivationCallbackFlag(true);

			DelayedSetStateCallback lv_delayedCollisionDeactivate
			{
				.m_callback{[this, lv_stateValue] {this->SetCollisionState(lv_stateValue); }},
				.m_currentFrame = 0U,
				.m_maxNumFrames = m_frameCountToDeactivateCollision
			};
			l_timer.AddSetStateCallback(std::move(lv_delayedCollisionDeactivate));

			m_repeatableAnimationComponent->SetVisibleState(false);
			LOG(Severity::INFO, Channel::PROGRAM_LOGIC, "2 callbacks have been recorded for an asteroid entity.");
			m_firstCollision = false;

		}

	}

}