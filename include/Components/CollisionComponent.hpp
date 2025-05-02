#pragma once



#include "Components/Component.hpp"
#include "Entities/EntityHandle.hpp"


namespace Asteroid
{

	class Entity;
	struct CollisionReactionContext;
	class DelayDeactiveBasedStateComponent;

	class CollisionComponent : public Component
	{

	public:

		CollisionComponent(EntityHandle l_ownerEntityHandle
		, DelayDeactiveBasedStateComponent* l_delayedDeactiveComponent);


		virtual void CollisionReaction(Entity& l_entityItCollidedWith, CollisionReactionContext& l_collisionReactContext) = 0;


		void ResetCollision();

	protected:

		bool m_firstCollision{false};
		bool m_resetCollision{ true };

		DelayDeactiveBasedStateComponent* m_delayedDeactiveComponent{};
	};


}