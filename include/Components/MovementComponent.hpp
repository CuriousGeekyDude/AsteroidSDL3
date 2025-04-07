#pragma once




#include <glm.hpp>
#include "Components/Component.hpp"

namespace Asteroid
{
	class Entity;
	class InputSystem;

	class MovementComponent : public Component
	{
	public:
		
		MovementComponent(Entity* l_ownerEntity, const InputSystem* l_inputSystem);

		virtual ~MovementComponent() = default;

		const glm::mat3& GetTransform() const;

	protected:
		glm::mat3 m_transform{};
		const InputSystem* m_inputSystem;
	};
}