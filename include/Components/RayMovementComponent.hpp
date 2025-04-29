#pragma once





#include "Components/MovementComponent.hpp"



namespace Asteroid
{
	class RayMovementComponent : public MovementComponent
	{
	public:

		RayMovementComponent(EntityHandle l_ownerEntityHandle);

		void SetInitialPos(const glm::vec2& l_initialPos);
		void SetRayDirection(const glm::vec2& l_direction);
		void SetInitialT(const float l_initialT);

		virtual bool Update(UpdateComponents& l_updateContext) override;

	private:
		glm::vec2 m_initialPos{};
		glm::vec2 m_rayDirection{};
		float m_initialT{};
	};
}