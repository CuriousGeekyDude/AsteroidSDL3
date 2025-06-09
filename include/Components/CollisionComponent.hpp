#pragma once



#include "Components/Component.hpp"
#include "Entities/EntityHandle.hpp"


namespace Asteroid
{

	class Entity;
	class IndefiniteRepeatableAnimationComponent;
	class CallbacksTimer;
	class IEvent;
	
	class CollisionComponent : public Component
	{

	public:

		CollisionComponent();


		virtual void CollisionReaction(IEvent*) = 0;



		void Init(EntityHandle l_ownerEntityHandle, const uint32_t l_frameCountToActivateCollision
			, const uint32_t l_frameCountToDeactivateCollision
			, const bool l_isCollisionActive
			, IndefiniteRepeatableAnimationComponent* l_repeatableAnimComponent);



		void SetCollisionState(const bool l_collisionState);


		bool GetCollisionState() const;

		bool IsCollisionReset() const;
		bool IsFirstCollision() const;

		void SetCollisionResetFlag(const bool l_resetCollision);
		void SetCollisionFirstFlag(const bool l_collisionFirst);

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