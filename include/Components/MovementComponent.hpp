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

		void SetSpeed(const glm::vec2& l_newSpeed);

		float GetCurrentAngleOfRotation() const;

	protected:
		glm::mat3 m_transform{};
		float m_theta{};
		const InputSystem* m_inputSystem;

		/// <summary>
		///Default speed for every component that moves.
		/// </summary>
		glm::vec2 m_speed{0.f};
	};
}