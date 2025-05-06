#pragma once



#include "Components/Component.hpp"
#include "Entities/EntityHandle.hpp"


namespace Asteroid
{

	class Entity;
	
	class CollisionComponent : public Component
	{

	public:

		CollisionComponent(EntityHandle l_ownerEntityHandle);


		virtual void CollisionReaction(Entity& l_entityItCollidedWith, Entity& l_ownerEntity) = 0;


		void ResetCollision();

	protected:

		bool m_firstCollision{false};
		bool m_resetCollision{ true };

	};


}