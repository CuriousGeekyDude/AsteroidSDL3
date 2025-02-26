#pragma once




#include <glm.hpp>
#include "Components/Component.hpp"

namespace Asteroid
{
	class Entity;

	class MovementComponent : public Component
	{
	public:
		
		MovementComponent(Entity* l_ownerEntity);

		virtual ~MovementComponent() = default;

		const glm::mat3& GetTransform() const;

	protected:
		glm::mat3 m_transform{};
	};
}