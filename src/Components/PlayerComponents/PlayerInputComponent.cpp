




#include "Components/PlayerComponents/PlayerInputComponent.hpp"
#include "Components/MovementComponent.hpp"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <SDL3/SDL.h>



namespace Asteroid
{


	PlayerInputComponent::PlayerInputComponent()
		:m_keyStates{}
	{

	}


	bool PlayerInputComponent::Update(float l_lastFrameElapsedTime)
	{
		
		m_keyStates.fill(false);

		//glm::mat3 lv_deltaTransform = glm::identity<glm::mat3>();

		ProcessKeyboardInput();
		ProcessMouseInput();

		return true;

	}


	void PlayerInputComponent::ProcessKeyboardInput()
	{

		/*glm::vec3 lv_deltaPos{0.f};
		constexpr float lv_speedDamper{ 0.1f };*/

		const bool* lv_keyStates = SDL_GetKeyboardState(nullptr);

		if (true == lv_keyStates[SDL_SCANCODE_W]) {
			m_keyStates[(int)Keys::KEY_W] = true;
		}
		if (true == lv_keyStates[SDL_SCANCODE_S]) {
			m_keyStates[(int)Keys::KEY_S] = true;
		}
		if (true == lv_keyStates[SDL_SCANCODE_D]) {
			m_keyStates[(int)Keys::KEY_D] = true;
		}
		if (true == lv_keyStates[SDL_SCANCODE_A]) {
			m_keyStates[(int)Keys::KEY_A] = true;
		}


		/*if (true == lv_keyStates[SDL_SCANCODE_W]) {
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
		l_deltaTransform[2][1] = lv_deltaPos.y;*/

	}

	void PlayerInputComponent::ProcessMouseInput()
	{

	}

	const std::array<bool, 4>& PlayerInputComponent::GetKeyStates() const
	{
		return m_keyStates;
	}

}