





#include "Components/CollisionComponents/BulletCollisionComponent.hpp"
#include "Entities/Entity.hpp"
#include "Components/StateComponents/ActiveBasedStateComponent.hpp"


namespace Asteroid
{

	
	BulletCollisionComponent::BulletCollisionComponent(EntityHandle l_ownerEntityHandle)
		:CollisionComponent(l_ownerEntityHandle)
	{

	}

	bool BulletCollisionComponent::Update(UpdateComponents& l_updateContext)
	{
		return true;
	}


	void BulletCollisionComponent::CollisionReaction(Entity& l_entityItCollidedWith, Entity& l_ownerEntity)
	{
		if (EntityType::BULLET == l_entityItCollidedWith.GetType() || EntityType::PLAYER == l_entityItCollidedWith.GetType()) {
			return;
		}

		if (true == m_resetCollision) {
			m_firstCollision = true;
			m_resetCollision = false;
		}


		if (false == m_resetCollision && true == m_firstCollision) {


			ActiveBasedStateComponent* lv_activeComponent = (ActiveBasedStateComponent*)l_ownerEntity.GetComponent(ComponentTypes::ACTIVE_BASED_STATE);

			lv_activeComponent->SetActiveState(false);

			m_firstCollision = false;

		}

	}

}