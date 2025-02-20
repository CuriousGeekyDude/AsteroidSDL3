




#include "Components/PlayerComponents/PlayerInputComponent.hpp"
#include "Components/MovementComponent.hpp"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <SDL3/SDL.h>



namespace Asteroid
{


	PlayerInputComponent::PlayerInputComponent(MovementComponent* l_movementComponent)
		:m_movementComponent(l_movementComponent)
	{

	}


	bool PlayerInputComponent::Update(float l_lastFrameElapsedTime)
	{
		
		glm::mat3 lv_deltaTransform = glm::identity<glm::mat3>();

		ProcessKeyboardInput(l_lastFrameElapsedTime, lv_deltaTransform);
		ProcessMouseInput(l_lastFrameElapsedTime, lv_deltaTransform);

		m_movementComponent->UpdateDeltaTransform(lv_deltaTransform);

		return true;

	}


	void PlayerInputComponent::ProcessKeyboardInput(float l_lastFrameElapsedTime, glm::mat3& l_deltaTransform)
	{

		glm::vec3 lv_deltaPos{0.f};
		constexpr float lv_speedDamper{ 0.1f };

		const bool* lv_keyStates = SDL_GetKeyboardState(nullptr);


		if (true == lv_keyStates[SDL_SCANCODE_W]) {
			lv_deltaPos.y = -1.f * (lv_speedDamper * l_lastFrameElapsedTime);
		}
		if (true == lv_keyStates[SDL_SCANCODE_S]) {
			lv_deltaPos.y = (lv_speedDamper * l_lastFrameElapsedTime);
		}
		if (true == lv_keyStates[SDL_SCANCODE_D]) {
			lv_deltaPos.x = (lv_speedDamper * l_lastFrameElapsedTime);
		}
		if (true == lv_keyStates[SDL_SCANCODE_A]) {
			lv_deltaPos.x = -1.f * (lv_speedDamper * l_lastFrameElapsedTime);
		}

		l_deltaTransform[2][0] = lv_deltaPos.x;
		l_deltaTransform[2][1] = lv_deltaPos.y;

	}

	void PlayerInputComponent::ProcessMouseInput(float l_lastFrameElapsedTime, glm::mat3& l_deltaTransform)
	{

	}

}