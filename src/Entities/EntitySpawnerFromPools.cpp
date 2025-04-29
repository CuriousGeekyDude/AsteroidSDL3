



#include "Entities/EntitySpawnerFromPools.hpp"
#include "Systems/InputSystem.hpp"
#include "Engine.hpp"
#include "Components/RayMovementComponent.hpp"
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
		m_bulletsPool.Init(l_type, l_firstEntityIndex, l_totalNumEntities);
	}

	void EntitySpawnerFromPools::SpawnNewEntitiesIfConditionsMet()
	{
		using namespace LogSystem;

		if (true == BulletSpawnConditionMet()) {


			auto lv_nextInactiveBulletIdx = m_bulletsPool.GetNextInactiveEntityHandle();
			LOG(Severity::INFO, Channel::MEMORY, "The next inactive bullet has index %u", lv_nextInactiveBulletIdx.m_entityHandle);

			auto& lv_bullet = m_engine->GetEntityFromHandle(lv_nextInactiveBulletIdx.m_entityHandle);
			lv_bullet.SetActive();
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
	}


	void EntitySpawnerFromPools::UpdatePools()
	{
		m_bulletsPool.Update(m_engine->GetEntities());
	}

	bool EntitySpawnerFromPools::BulletSpawnConditionMet()
	{
		using namespace LogSystem;

		const auto& lv_inputSystem = m_engine->GetInputSystem();
		if (true == lv_inputSystem.IsKeyPressedWithRepetition(InputSystem::Keys::KEY_F) && true == lv_inputSystem.IsMouseHidden()) {

			return true;
		}
		else {
			return false;
		}
	}
}