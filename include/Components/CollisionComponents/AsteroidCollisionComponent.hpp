




#include "Components/CollisionComponent.hpp"



namespace Asteroid
{
	
	class Entity;

	class AsteroidCollisionComponent : public CollisionComponent
	{
	public:

		AsteroidCollisionComponent(EntityHandle l_ownerEntityHandle);


		bool Update(UpdateComponents& l_updateContext) override;


		void CollisionReaction(Entity& l_entityItCollidedWith, Entity& l_ownerEntity) override;

	private:


	};

}