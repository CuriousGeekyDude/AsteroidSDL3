





#include "Components/CollisionComponents/AsteroidCollisionComponent.hpp"
#include "Systems/Animation.hpp"
#include "Systems/CollisionReactionContext.hpp"
#include "Entities/Entity.hpp"
#include "Components/RayMovementComponent.hpp"
#include "Components/StateComponents/DelayDeactiveBasedStateComponent.hpp"


namespace Asteroid
{

	AsteroidCollisionComponent::AsteroidCollisionComponent(EntityHandle l_ownerEntityHandle, const RayMovementComponent* l_ownerMovComponent, DelayDeactiveBasedStateComponent* l_delayedDeactiveComponent)
		:CollisionComponent(l_ownerEntityHandle, l_delayedDeactiveComponent)
		,m_ownerMovComponent(l_ownerMovComponent)
	{

	}



	bool AsteroidCollisionComponent::Update(UpdateComponents& l_updateContext)
	{
		return true;
	}



	void AsteroidCollisionComponent::CollisionReaction(Entity& l_entityItCollidedWith, CollisionReactionContext& l_collisionReactContext)
	{
		
		if (true == m_resetCollision) {
			m_firstCollision = true;
			m_resetCollision = false;
		}



		if (false == m_resetCollision && true == m_firstCollision) {

			auto* lv_ownerEntity = l_collisionReactContext.m_ownerEntity;

			l_collisionReactContext.m_animationSystem
				->InitNewAnimation(AnimationType::EXPLOSION_FIRE_ASTEROID
				, lv_ownerEntity->GetCurrentPos(), m_ownerMovComponent->GetCurrentAngleOfRotation());
			m_delayedDeactiveComponent->StartCount();
			m_firstCollision = false;

		}

	}

}