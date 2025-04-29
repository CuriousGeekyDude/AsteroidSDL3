



#include "Systems/Collision.hpp"
#include "Entities/Entity.hpp"

namespace Asteroid
{


	namespace Collision
	{
		void CollisionReaction(Entity& l_entity1, Entity& l_entity2) {
			
			const auto lv_entityType1 = l_entity1.GetType();
			const auto lv_entityType2 = l_entity2.GetType();

			if ((EntityType::ASTEROID == lv_entityType1 || EntityType::ASTEROID == lv_entityType2)
				&&
				(EntityType::BULLET == lv_entityType1 || EntityType::BULLET == lv_entityType2)) {

				l_entity1.SetInactive();
				l_entity2.SetInactive();


				return;

			}

			if (EntityType::ASTEROID == lv_entityType1 && EntityType::ASTEROID == lv_entityType2) {
				l_entity1.SetInactive();
				l_entity2.SetInactive();


				return;
			}

			if ((EntityType::ASTEROID == lv_entityType1 || EntityType::ASTEROID == lv_entityType2)
				&&
				(EntityType::PLAYER == lv_entityType1 || EntityType::PLAYER == lv_entityType2)) {

				if (EntityType::ASTEROID == lv_entityType1) {
					l_entity1.SetInactive();
				}
				else {
					l_entity2.SetInactive();
				}
			}
		}


	}

}