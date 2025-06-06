



#include "Components/RayMovementComponent.hpp"
#include "Engine.hpp"
#include "Components/UpdateComponents.hpp"


namespace Asteroid
{

	RayMovementComponent::RayMovementComponent()
	{

	}

	void RayMovementComponent::Init(EntityHandle l_ownerEntityHandle)
	{
		m_ownerEntityHandle = l_ownerEntityHandle;
	}

	void RayMovementComponent::SetInitialPos(const glm::vec2& l_initialPos)
	{
		m_initialPos = l_initialPos;
	}
	void RayMovementComponent::SetRayDirection(const glm::vec2& l_direction)
	{
		m_rayDirection = l_direction;
	}
	void RayMovementComponent::SetInitialT(const float l_initialT)
	{
		m_initialT = l_initialT;
	}

	bool RayMovementComponent::Update(UpdateComponents& l_updateContext)
	{

		if (false == m_pauseMovement) {
			auto& lv_ownerEntity = l_updateContext.m_engine->GetEntityFromHandle(m_ownerEntityHandle);

			const auto& lv_currentPos = lv_ownerEntity.GetCurrentPos();

			const glm::vec2 lv_newPos = lv_currentPos + (m_speed.x * l_updateContext.m_deltaTime)*m_rayDirection;

			lv_ownerEntity.SetCurrentPos(lv_newPos);

		}

		return true;
	}

	const glm::vec2& RayMovementComponent::GetInitialPos() const
	{
		return m_initialPos;
	}
	const glm::vec2& RayMovementComponent::GetRayDirection() const
	{
		return m_rayDirection;
	}
	float RayMovementComponent::GetInitalT() const
	{
		return m_initialT;
	}

}