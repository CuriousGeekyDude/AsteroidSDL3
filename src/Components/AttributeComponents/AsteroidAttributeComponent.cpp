





#include "Components/AttributeComponents/AsteroidAttributeComponent.hpp"
#include "Components/RayMovementComponent.hpp"
#include "Components/UpdateComponents.hpp"
#include "Engine.hpp"


namespace Asteroid
{

	AsteroidAttributeComponent::AsteroidAttributeComponent()
	{

	}



	void AsteroidAttributeComponent::SetState(const AsteroidStates l_newState)
	{
		m_state = l_newState;
	}


	bool AsteroidAttributeComponent::Update(UpdateComponents& l_updateContext)
	{
		if (AsteroidStates::AGGRESIVE == m_state) {

			const auto& lv_ownerEntity = l_updateContext.m_engine->GetEntityFromHandle(m_ownerEntityHandle);
			const auto& lv_currentPos = lv_ownerEntity.GetCurrentPos();
			const auto& lv_playerPos = l_updateContext.m_engine->m_entityConnector.RequestPositionFromPlayer();
			auto lv_normalizedDir = lv_playerPos - lv_currentPos;

			lv_normalizedDir = glm::normalize(lv_normalizedDir);

			m_rayMovement->SetRayDirection(lv_normalizedDir);
		}

		return true;
	}


	void AsteroidAttributeComponent::Init(EntityHandle l_ownerEntityHandle, uint32_t l_hp
		, const AsteroidStates l_state, RayMovementComponent* l_rayMovement)
	{
		AttributeComponent::Init(l_ownerEntityHandle, l_hp);

		m_state = l_state;
		m_rayMovement = l_rayMovement;
	}



	AsteroidStates AsteroidAttributeComponent::GetState() const
	{
		return m_state;
	}

}
