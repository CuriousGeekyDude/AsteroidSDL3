#pragma once






#include "Components/CollisionComponent.hpp"


namespace Asteroid
{

	class PlayerAttributeComponent;

	class PlayerCollisionComponent : public CollisionComponent
	{
	public:

		PlayerCollisionComponent();

		bool Update(UpdateComponents& l_updateContext) override;



		void Init(EntityHandle l_ownerEntityHandle
			, const uint32_t l_frameCountToActivateCollision
			, const uint32_t l_frameCountToDeactivateCollision
			, const bool l_isCollisionActive
			, IndefiniteRepeatableAnimationComponent* l_repeatableAnimComponent
			, PlayerAttributeComponent* l_playerAttribComponent);


		void CollisionReaction(Entity& l_entityItCollidedWith, Entity& l_ownerEntity, CallbacksTimer& l_timer) override;



	private:

		PlayerAttributeComponent* m_attribComponent{};
	};


}