



#include "Components/MovementComponent.hpp"
#include <gtc/matrix_transform.hpp>


namespace Asteroid
{

	MovementComponent::MovementComponent(Entity* l_ownerEntity)
		:Component(l_ownerEntity)
		, m_transform(glm::identity<glm::mat3>())
	{

	}

	const glm::mat3& MovementComponent::GetTransform() const
	{
		return m_transform;
	}
}