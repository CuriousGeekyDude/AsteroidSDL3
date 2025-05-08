#pragma once






#include "Components/CollisionComponent.hpp"



namespace Asteroid
{
	class ActiveBasedStateComponent;

	class BulletCollisionComponent : public CollisionComponent
	{
	public:

		BulletCollisionComponent();

		bool Update(UpdateComponents& l_updateContext) override;

		void CollisionReaction(Entity& l_entityItCollidedWith, Entity& l_ownerEntity, CallbacksTimer& l_timer) override;


		void Init(EntityHandle l_ownerEntityHandle
			, const uint32_t l_frameCountToActivateCollision
			, const uint32_t l_frameCountToDeactivateCollision
			, const bool l_isCollisionActive
			, IndefiniteRepeatableAnimationComponent* l_repeatableAnimComponent
			, const ActiveBasedStateComponent* l_activeComponent);


	private:

		const ActiveBasedStateComponent* m_activeComponent{};

	};

}