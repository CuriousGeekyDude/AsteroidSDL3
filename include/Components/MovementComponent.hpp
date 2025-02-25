#pragma once




#include <glm.hpp>
#include "Components/Component.hpp"

namespace Asteroid
{
	class MovementComponent : public Component
	{
	public:
		
		MovementComponent();

		virtual ~MovementComponent() = default;

		const glm::mat3& GetTransform() const;

	protected:
		glm::mat3 m_transform{};
	};
}