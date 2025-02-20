



#include "Components/MovementComponent.hpp"
#include <gtc/matrix_transform.hpp>


namespace Asteroid
{

	MovementComponent::MovementComponent()
		:m_transform(glm::identity<glm::mat3>())
		,m_deltaTransform(glm::identity<glm::mat3>())
	{

	}


	void MovementComponent::UpdateDeltaTransform(const glm::mat3& l_deltaTransform)
	{
		m_deltaTransform = l_deltaTransform;
	}


	bool MovementComponent::Update(float l_lastFrameElapsedTime)
	{
		m_transform = m_deltaTransform * m_transform;

		return true;
	}

	const glm::mat3& MovementComponent::GetTransform() const
	{
		return m_transform;
	}
}