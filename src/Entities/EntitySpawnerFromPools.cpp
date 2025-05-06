



#include "Entities/EntitySpawnerFromPools.hpp"
#include "Systems/InputSystem.hpp"
#include "Engine.hpp"
#include "Components/RayMovementComponent.hpp"
#include "Components/StateComponents/ActiveBasedStateComponent.hpp"
#include "Components/StateComponents/VisibilityBasedStateComponent.hpp"
#include "Entities/Entity.hpp"


#include "Systems/LogSystem.hpp"

namespace Asteroid
{
	EntitySpawnerFromPools::EntitySpawnerFromPools(Engine* l_engine)
		:m_engine(l_engine)
	{

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

		if (true == BulletSpawnConditionMet()) {

			
			auto lv_nextInactiveBulletIdx = m_bulletsPool.GetNextInactiveEntityHandle();

			LOG(Severity::INFO, Channel::GRAPHICS, "Bullet with index %u is being fetched", lv_nextInactiveBulletIdx);

			auto& lv_bullet = m_engine->GetEntityFromHandle(lv_nextInactiveBulletIdx.m_entityHandle);

			ActiveBasedStateComponent* lv_activeComp = (ActiveBasedStateComponent*)lv_bullet.GetComponent(ComponentTypes::ACTIVE_BASED_STATE);

			lv_activeComp->SetActiveState(true);
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
			}

		}

		if (true == AsteroidSpawnConditionMet()) {


			auto lv_nextInactiveAsteroidIdx = m_asteroidPool.GetNextInactiveEntityHandle();

			LOG(Severity::INFO, Channel::GRAPHICS, "Asteroid with index %u is being fetched", lv_nextInactiveAsteroidIdx);

			glm::ivec2 lv_windowRes{};
			m_engine->GetCurrentWindowSize(lv_windowRes);

			auto& lv_asteroid = m_engine->GetEntityFromHandle(lv_nextInactiveAsteroidIdx.m_entityHandle);

			ActiveBasedStateComponent* lv_activeComp = (ActiveBasedStateComponent*)lv_asteroid.GetComponent(ComponentTypes::ACTIVE_BASED_STATE);
			VisibilityBasedStateComponent* lv_visibilityComp = (VisibilityBasedStateComponent*)lv_asteroid.GetComponent(ComponentTypes::VISIBILITY_BASED_STATE);

			lv_activeComp->SetActiveState(true);
			lv_visibilityComp->SetVisibility(true);

			glm::vec2 lv_direction{-1.f, 0.f};

			RayMovementComponent* lv_asteroidMovComponent = (RayMovementComponent*)lv_asteroid.GetComponent(ComponentTypes::MOVEMENT);
			constexpr float lv_initialT{ 20.f };

			lv_asteroidMovComponent->SetSpeed(glm::vec2{ 0.1f });
			lv_asteroidMovComponent->SetRayDirection(lv_direction);
			lv_asteroidMovComponent->SetInitialT(lv_initialT);
			lv_asteroidMovComponent->SetAngleOfRotation(0.f);
			lv_asteroidMovComponent->SetInitialPos({lv_windowRes.x, lv_windowRes.y/2.f});
			

		}
	}


	void EntitySpawnerFromPools::UpdatePools()
	{
		m_bulletsPool.Update(m_engine->GetEntities());
		m_asteroidPool.Update(m_engine->GetEntities());
	}


	bool EntitySpawnerFromPools::AsteroidSpawnConditionMet()
	{
		const auto& lv_inputSystem = m_engine->GetInputSystem();
		if (true == lv_inputSystem.IsNoRepetitionAllowedKeyPressed(InputSystem::Keys::KEY_T) && true == lv_inputSystem.IsMouseHidden()) {

			return true;
		}
		else {
			return false;
		}
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