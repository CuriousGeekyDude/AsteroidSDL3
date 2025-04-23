



#include "Components/RayMovementComponent.hpp"
#include "Engine.hpp"
#include "Entities/Entity.hpp"


namespace Asteroid
{

	RayMovementComponent::RayMovementComponent(EntityHandle l_ownerEntityHandle, Engine* l_engine)
		:MovementComponent(l_ownerEntityHandle, l_engine)
	{

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

	bool RayMovementComponent::Update(float l_deltaTime)
	{
		auto& lv_ownerEntity = m_engine->GetEntityFromHandle(m_ownerEntityHandle);

		m_initialT += m_speed.x * l_deltaTime;

		const glm::vec2 lv_newPos = m_initialPos + (m_initialT) * m_rayDirection;
		m_transform[0][0] = lv_newPos.x;
		m_transform[0][1] = lv_newPos.y;

		lv_ownerEntity.SetCurrentPos(lv_newPos);


		return true;
	}

}