#pragma once




#include "EntityPool.hpp"
#include <vector>
#include <array>
#include <random>


namespace Asteroid
{

	class InputSystem;
	class Engine;
	
	class EntitySpawnerFromPools
	{
	public:

		EntitySpawnerFromPools(Engine* l_engine);

		void InitPool(const EntityType l_type, const uint32_t l_firstEntityIndex, const uint32_t l_totalNumEntities);
		void SpawnNewEntitiesIfConditionsMet(const uint32_t l_level);

		void UpdatePools();

		void ResetPools();

	private:

		bool BulletSpawnConditionMet();
		bool AsteroidSpawnConditionMet();


		void GenerateRandomIndexCellNumbers(const uint32_t l_maxNumCurrentCells);

	private:

		Engine* m_engine;
		EntityPool m_bulletsPool;

		static constexpr uint32_t m_asteroidMinNumInScene{20U};
		std::array<uint32_t, m_asteroidMinNumInScene> m_randomIndexCellNumbers{};
		std::array<float, m_asteroidMinNumInScene> m_randomDirectionsForAsteroids{};
		EntityPool m_asteroidPool;


		std::mt19937 m_mt;
	};
}