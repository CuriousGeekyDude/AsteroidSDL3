



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



			m_initialT += m_speed.x * l_updateContext.m_deltaTime;

			const glm::vec2 lv_newPos = m_initialPos + (m_initialT)*m_rayDirection;
			m_transform[2][0] = lv_newPos.x;
			m_transform[2][1] = lv_newPos.y;

			lv_ownerEntity.SetCurrentPos(lv_newPos);

		}

		return true;
	}

}