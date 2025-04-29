



#include "Components/MovementComponent.hpp"
#include <gtc/matrix_transform.hpp>


namespace Asteroid
{

	MovementComponent::MovementComponent(EntityHandle l_ownerEntityHandle)
		:Component(l_ownerEntityHandle)
	{

	}

	const glm::mat3& MovementComponent::GetTransform() const
	{
		return m_transform;
	}

	const glm::vec2& MovementComponent::GetSpeed() const
	{
		return m_speed;
	}



	void MovementComponent::SetSpeed(const glm::vec2& l_newSpeed)
	{
		m_speed = l_newSpeed;
	}

	float MovementComponent::GetCurrentAngleOfRotation() const
	{
		return m_theta;
	}

	void MovementComponent::SetAngleOfRotation(const float l_theta)
	{
		m_theta = l_theta;
	}
}