#pragma once






#include "Components/CollisionComponent.hpp"


namespace Asteroid
{

	class PlayerCollisionComponent : public CollisionComponent
	{
	public:

		PlayerCollisionComponent();

		bool Update(UpdateComponents& l_updateContext) override;



		void Init(EntityHandle l_ownerEntityHandle
			, const uint32_t l_frameCountToActivateCollision
			, const uint32_t l_frameCountToDeactivateCollision
			, const bool l_isCollisionActive
			, IndefiniteRepeatableAnimationComponent* l_repeatableAnimComponent);


		void CollisionReaction(Entity& l_entityItCollidedWith, Entity& l_ownerEntity, CallbacksTimer& l_timer) override;

	};


}