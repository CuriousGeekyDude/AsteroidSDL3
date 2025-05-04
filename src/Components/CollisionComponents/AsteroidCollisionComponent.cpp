





#include "Components/CollisionComponents/AsteroidCollisionComponent.hpp"
#include "Components/AnimationComponent.hpp"
#include "Entities/Entity.hpp"
#include "Components/StateComponents/ActiveBasedStateComponent.hpp"
#include "Components/StateComponents/VisibilityBasedStateComponent.hpp"
#include "Components/StateComponents/CollisionBasedStateComponent.hpp"


namespace Asteroid
{

	AsteroidCollisionComponent::AsteroidCollisionComponent(EntityHandle l_ownerEntityHandle)
		:CollisionComponent(l_ownerEntityHandle)
	{

	}



	bool AsteroidCollisionComponent::Update(UpdateComponents& l_updateContext)
	{
		return true;
	}



	void AsteroidCollisionComponent::CollisionReaction(Entity& l_entityItCollidedWith, Entity& l_ownerEntity)
	{
		
		if (true == m_resetCollision) {
			m_firstCollision = true;
			m_resetCollision = false;
		}



		if (false == m_resetCollision && true == m_firstCollision) {


			CollisionBasedStateComponent* lv_collisionStateComp = (CollisionBasedStateComponent*)l_ownerEntity.GetComponent(ComponentTypes::COLLISION_BASED_STATE);


			if (true == lv_collisionStateComp->GetCollisionState()) {
				AnimationComponent* lv_fireExplosionAnimation = (AnimationComponent*)l_ownerEntity.GetComponent(ComponentTypes::EXPLOSION_FIRE_ASTEROID_ANIMATION);
				ActiveBasedStateComponent* lv_activeComponent = (ActiveBasedStateComponent*)l_ownerEntity.GetComponent(ComponentTypes::ACTIVE_BASED_STATE);
				lv_fireExplosionAnimation->StartAnimation();
				lv_activeComponent->StartCount();
				lv_collisionStateComp->StartCollisionDeactivation();
				m_firstCollision = false;
			}

		}

	}

}