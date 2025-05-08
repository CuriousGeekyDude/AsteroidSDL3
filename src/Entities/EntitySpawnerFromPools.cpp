



#include "Entities/EntitySpawnerFromPools.hpp"
#include "Systems/InputSystem.hpp"
#include "Engine.hpp"
#include "Components/RayMovementComponent.hpp"
#include "Components/StateComponents/ActiveBasedStateComponent.hpp"
#include "Components/IndefiniteRepeatableAnimationComponent.hpp"
#include "Components/CollisionComponent.hpp"
#include "Entities/Entity.hpp"


#include "Systems/LogSystem.hpp"

namespace Asteroid
{
	EntitySpawnerFromPools::EntitySpawnerFromPools(Engine* l_engine)
		:m_engine(l_engine)
		,m_mt(std::random_device()())
	{

		constexpr float lv_deltaAngleDegrees{glm::two_pi<float>()/(float)m_asteroidMinNumInScene};
		for (uint32_t i = 0; i < (uint32_t)m_randomDirectionsForAsteroids.size(); ++i) {

			m_randomDirectionsForAsteroids[i] = (float)i*lv_deltaAngleDegrees;

		}

	}

	void EntitySpawnerFromPools::InitPool(const EntityType l_type, const uint32_t l_firstEntityIndex, const uint32_t l_totalNumEntities)
	{
		if (EntityType::BULLET == l_type) {
			m_bulletsPool.Init(l_type, l_firstEntityIndex, l_totalNumEntities);
		}
		if (EntityType::ASTEROID == l_type) {
			m_asteroidPool.Init(l_type, l_firstEntityIndex, l_totalNumEntities);
		}
	}

	void EntitySpawnerFromPools::SpawnNewEntitiesIfConditionsMet()
	{
		using namespace LogSystem;
		constexpr float lv_piOver180 = glm::pi<float>() / 180.f;

		if (true == BulletSpawnConditionMet()) {


			auto lv_nextInactiveBulletIdx = m_bulletsPool.GetNextInactiveEntityHandle();

			LOG(Severity::INFO, Channel::GRAPHICS, "Bullet with index %u is being fetched", lv_nextInactiveBulletIdx);

			auto& lv_bullet = m_engine->GetEntityFromHandle(lv_nextInactiveBulletIdx.m_entityHandle);

			auto* lv_collisionComponent = (CollisionComponent*)lv_bullet.GetComponent(ComponentTypes::COLLISION);
			auto* lv_entityMainAnimationComponent = (IndefiniteRepeatableAnimationComponent*)lv_bullet.GetComponent(ComponentTypes::INDEFINITE_ENTITY_ANIMATION);
			auto* lv_activeComponent = (ActiveBasedStateComponent*)lv_bullet.GetComponent(ComponentTypes::ACTIVE_BASED_STATE);
			lv_bullet.SetActiveState(true);
			lv_collisionComponent->SetCollisionState(true);
			lv_collisionComponent->Reset();
			lv_entityMainAnimationComponent->Reset();
			lv_entityMainAnimationComponent->SetVisibleState(true);
			lv_activeComponent->Reset();

			const auto& lv_currentPlayerPos = m_engine->m_entityConnector.RequestPositionFromPlayer();
			float lv_playerAngleOfRotation = m_engine->m_entityConnector.RequestAngleRotationFromPlayer();
			const auto& lv_mousePos = m_engine->GetInputSystem().GetMousePosRelativeToWindow();
			glm::vec2 lv_direction = lv_mousePos - lv_currentPlayerPos;

			RayMovementComponent* lv_bulletMovComponent = (RayMovementComponent*)lv_bullet.GetComponent(ComponentTypes::MOVEMENT);
			constexpr float lv_initialT{ 55.f };

			lv_bulletMovComponent->SetSpeed(glm::vec2{0.5f});

			if(0 == lv_direction.x && 0 == lv_direction.y) {
				lv_bulletMovComponent->SetRayDirection(lv_direction);
				lv_bulletMovComponent->SetInitialT(0.f);
				lv_bulletMovComponent->SetAngleOfRotation(lv_playerAngleOfRotation);
				lv_bulletMovComponent->SetInitialPos(glm::vec2{-100.f, -100.f});
			}
			else {
				lv_direction = glm::normalize(lv_direction);

				lv_bulletMovComponent->SetRayDirection(lv_direction);
				lv_bulletMovComponent->SetInitialT(lv_initialT);
				lv_bulletMovComponent->SetAngleOfRotation(lv_playerAngleOfRotation);
				lv_bulletMovComponent->SetInitialPos(lv_currentPlayerPos);
				lv_bullet.SetCurrentPos(lv_currentPlayerPos);
			}

		}

		if (true == AsteroidSpawnConditionMet()) {

			const Grid& lv_grid = m_engine->GetGrid();
			const auto& lv_centerPosCells = lv_grid.GetCurrentCenterPosCells();

			const uint32_t lv_totalNumCurrentCells = lv_grid.GetTotalNumCurrentCells();

			GenerateRandomIndexCellNumbers(lv_totalNumCurrentCells);
			
			for (uint32_t i = 0; i < m_asteroidMinNumInScene; ++i) {

				auto lv_nextInactiveAsteroidIdx = m_asteroidPool.GetNextInactiveEntityHandle();



				LOG(Severity::INFO, Channel::GRAPHICS, "Asteroid with index %u is being fetched", lv_nextInactiveAsteroidIdx);

				

				glm::vec2 lv_asteroidPos = lv_centerPosCells[m_randomIndexCellNumbers[i]];

				auto& lv_asteroid = m_engine->GetEntityFromHandle(lv_nextInactiveAsteroidIdx.m_entityHandle);

				auto* lv_collisionComponent = (CollisionComponent*)lv_asteroid.GetComponent(ComponentTypes::COLLISION);
				auto* lv_entityMainAnimationComponent = (IndefiniteRepeatableAnimationComponent*)lv_asteroid.GetComponent(ComponentTypes::INDEFINITE_ENTITY_ANIMATION);
				auto* lv_activeComponent = (ActiveBasedStateComponent*)lv_asteroid.GetComponent(ComponentTypes::ACTIVE_BASED_STATE);

				lv_asteroid.SetActiveState(true);
				lv_collisionComponent->SetCollisionState(true);
				lv_collisionComponent->Reset();
				lv_entityMainAnimationComponent->SetVisibleState(true);
				lv_activeComponent->Reset();


				glm::vec2 lv_direction{ std::cos(m_randomDirectionsForAsteroids[i] + lv_piOver180*m_randomIndexCellNumbers[i]), std::sin(m_randomDirectionsForAsteroids[i] + lv_piOver180*m_randomIndexCellNumbers[i])};

				RayMovementComponent* lv_asteroidMovComponent = (RayMovementComponent*)lv_asteroid.GetComponent(ComponentTypes::MOVEMENT);
				constexpr float lv_initialT{ 20.f };

				lv_asteroidMovComponent->SetSpeed(glm::vec2{ 0.05f });
				lv_asteroidMovComponent->SetRayDirection(lv_direction);
				lv_asteroidMovComponent->SetInitialT(lv_initialT);
				lv_asteroidMovComponent->SetAngleOfRotation(0.f);
				lv_asteroidMovComponent->SetInitialPos(lv_asteroidPos);

			}

		}
	}


	void EntitySpawnerFromPools::UpdatePools()
	{
		m_bulletsPool.Update(m_engine->GetEntities());
		m_asteroidPool.Update(m_engine->GetEntities());
	}



	void EntitySpawnerFromPools::GenerateRandomIndexCellNumbers(const uint32_t l_maxNumCurrentCells)
	{
		if (0U == l_maxNumCurrentCells) {
			return;
		}
		std::uniform_int_distribution<uint32_t> lv_randGenerator{ 0U, l_maxNumCurrentCells - 1 };
		m_randomIndexCellNumbers[0] = lv_randGenerator(m_mt);

		for (uint32_t i = 1; i < (uint32_t)m_randomIndexCellNumbers.size(); ++i) {
			m_randomIndexCellNumbers[i] = lv_randGenerator(m_mt);

			for (uint32_t j = 0; j < i; ++j) {
				if (m_randomIndexCellNumbers[j] == m_randomIndexCellNumbers[i]) {
					m_randomIndexCellNumbers[i] = lv_randGenerator(m_mt);
					j = 0U;
				}
			}

		}
	}


	bool EntitySpawnerFromPools::AsteroidSpawnConditionMet()
	{
		

		const uint32_t lv_totalNumActiveAsteroids = m_asteroidPool.GetTotalNumActiveEntities();

		if (m_asteroidMinNumInScene > lv_totalNumActiveAsteroids) {
			return true;
		}
		else {
			return false;
		}

		/*const auto& lv_inputSystem = m_engine->GetInputSystem();
		if (true == lv_inputSystem.IsNoRepetitionAllowedKeyPressed(InputSystem::Keys::KEY_T) && true == lv_inputSystem.IsMouseHidden()) {

			return true;
		}
		else {
			return false;
		}*/
	}

	bool EntitySpawnerFromPools::BulletSpawnConditionMet()
	{
		using namespace LogSystem;

		const auto& lv_inputSystem = m_engine->GetInputSystem();
		if (true == lv_inputSystem.IsNoRepetitionAllowedKeyPressed(InputSystem::Keys::KEY_F) && true == lv_inputSystem.IsMouseHidden()) {

			return true;
		}
		else {
			return false;
		}
	}
}