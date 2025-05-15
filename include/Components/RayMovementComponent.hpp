#pragma once





#include "Components/MovementComponent.hpp"



namespace Asteroid
{
	class RayMovementComponent : public MovementComponent
	{
	public:

		RayMovementComponent();

		void SetInitialPos(const glm::vec2& l_initialPos);
		void SetRayDirection(const glm::vec2& l_direction);
		void SetInitialT(const float l_initialT);

		virtual bool Update(UpdateComponents& l_updateContext) override;


		void Init(EntityHandle l_ownerEntityHandle);


		const glm::vec2& GetInitialPos() const;
		const glm::vec2& GetRayDirection() const;
		float GetInitalT() const;

	private:
		glm::vec2 m_initialPos{};
		glm::vec2 m_rayDirection{};
		float m_initialT{};
	};
}