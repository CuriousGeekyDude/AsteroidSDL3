#pragma once




#include "EntityPool.hpp"
#include <vector>


namespace Asteroid
{

	class InputSystem;
	class Engine;
	
	class EntitySpawnerFromPools
	{
	public:

		EntitySpawnerFromPools(Engine* l_engine);

		void InitPool(const EntityType l_type, const uint32_t l_firstEntityIndex, const uint32_t l_totalNumEntities);
		void SpawnNewEntitiesIfConditionsMet();

		void UpdatePools();


	private:

		bool BulletSpawnConditionMet();
		bool AsteroidSpawnConditionMet();

	private:

		Engine* m_engine;
		EntityPool m_bulletsPool;
		EntityPool m_asteroidPool;
	};
}