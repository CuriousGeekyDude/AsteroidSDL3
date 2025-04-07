



#include "Components/MovementComponent.hpp"
#include <gtc/matrix_transform.hpp>


namespace Asteroid
{

	MovementComponent::MovementComponent(Entity* l_ownerEntity, const InputSystem* l_inputSystem)
		:Component(l_ownerEntity)
		, m_transform(glm::identity<glm::mat3>())
		, m_inputSystem(l_inputSystem)
	{

	}

	const glm::mat3& MovementComponent::GetTransform() const
	{
		return m_transform;
	}
}