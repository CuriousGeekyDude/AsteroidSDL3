#pragma once




#include "Components/InputComponent.hpp"
#include <glm.hpp>


namespace Asteroid
{

	class MovementComponent;

	class PlayerInputComponent : public InputComponent
	{

	public:
		PlayerInputComponent(MovementComponent* l_movementComponent);


		bool Update(float l_lastFrameElapsedTime) override;



	protected:


		void ProcessKeyboardInput(float l_lastFrameElapsedTime, glm::mat3& l_deltaTransform);
		void ProcessMouseInput(float l_lastFrameElapsedTime, glm::mat3& l_deltaTransform);


	protected:


		MovementComponent* m_movementComponent;

	};
}

