#pragma once



#include "Components/Component.hpp"
#include "Entities/EntityHandle.hpp"


namespace Asteroid
{

	class Entity;
	class IndefiniteRepeatableAnimationComponent;
	class CallbacksTimer;

	
	class CollisionComponent : public Component
	{

	public:

		CollisionComponent();


		virtual void CollisionReaction(Entity& l_entityItCollidedWith, Entity& l_ownerEntity, CallbacksTimer& l_timer) = 0;



		void Init(EntityHandle l_ownerEntityHandle, const uint32_t l_frameCountToActivateCollision
			, const uint32_t l_frameCountToDeactivateCollision
			, const bool l_isCollisionActive
			, IndefiniteRepeatableAnimationComponent* l_repeatableAnimComponent);



		void SetCollisionState(const bool l_collisionState);


		bool GetCollisionState() const;

		void Reset();

		uint32_t GetFrameCountToActivateCollision() const;
		uint32_t GetFrameCountToDeactivateCollision() const;

		virtual ~CollisionComponent() = default;


	protected:

		
		bool m_isCollisionActive{true};
		bool m_resetCollision{true};
		bool m_firstCollision{false};

		IndefiniteRepeatableAnimationComponent* m_repeatableAnimationComponent{};
		uint32_t m_frameCountToActivateCollision{};
		uint32_t m_frameCountToDeactivateCollision{};
	};


}