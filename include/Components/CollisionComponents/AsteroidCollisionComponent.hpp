




#include "Components/CollisionComponent.hpp"



namespace Asteroid
{
	
	class Entity;
	class OnceRepeatableAnimationComponent;
	class ActiveBasedStateComponent;

	class AsteroidCollisionComponent : public CollisionComponent
	{
	public:

		AsteroidCollisionComponent();


		bool Update(UpdateComponents& l_updateContext) override;


		void CollisionReaction(Entity& l_entityItCollidedWith, Entity& l_ownerEntity, CallbacksTimer& l_timer) override;


		void Init(EntityHandle l_ownerEntityHandle
			, const uint32_t l_frameCountToActivateCollision
			, const uint32_t l_frameCountToDeactivateCollision
			, const bool l_isCollisionActive
			, IndefiniteRepeatableAnimationComponent* l_repeatableAnimComponent
			, OnceRepeatableAnimationComponent* l_fireExplosionAnimation
			, ActiveBasedStateComponent* l_activeComponent);


	private:

		OnceRepeatableAnimationComponent* m_fireExplosionAnimation{};
		ActiveBasedStateComponent* m_activeComponent{};
		uint32_t m_hitBullet{};
	};

}