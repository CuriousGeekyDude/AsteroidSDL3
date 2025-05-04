





#include "Components/CollisionComponents/BulletCollisionComponent.hpp"
#include "Entities/Entity.hpp"
#include "Systems/CollisionReactionContext.hpp"
#include "Components/RayMovementComponent.hpp"


namespace Asteroid
{

	
	BulletCollisionComponent::BulletCollisionComponent(EntityHandle l_ownerEntityHandle, const RayMovementComponent* l_ownerMovComponent, DelayDeactiveBasedStateComponent* l_delayedDeactiveComponent)
		:CollisionComponent(l_ownerEntityHandle, l_delayedDeactiveComponent)
		,m_ownerMovComponent(l_ownerMovComponent)
	{

	}

	bool BulletCollisionComponent::Update(UpdateComponents& l_updateContext)
	{
		return true;
	}


	void BulletCollisionComponent::CollisionReaction(Entity& l_entityItCollidedWith, CollisionReactionContext& l_collisionReactContext)
	{
		if (EntityType::BULLET == l_entityItCollidedWith.GetType() || EntityType::PLAYER == l_entityItCollidedWith.GetType()) {
			return;
		}

		if (true == m_resetCollision) {
			m_firstCollision = true;
			m_resetCollision = false;
		}


		if (false == m_resetCollision && true == m_firstCollision) {

			auto* lv_ownerEntity = l_collisionReactContext.m_ownerEntity;
			l_collisionReactContext.m_ownerEntity->SetInactive();
			m_firstCollision = false;

		}

	}

}