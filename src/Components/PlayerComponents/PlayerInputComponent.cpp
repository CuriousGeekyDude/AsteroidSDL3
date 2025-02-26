




#include "Components/PlayerComponents/PlayerInputComponent.hpp"
#include "Components/MovementComponent.hpp"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <SDL3/SDL.h>



namespace Asteroid
{


	PlayerInputComponent::PlayerInputComponent(Entity* l_ownerEntity)
		:InputComponent(l_ownerEntity)
		, m_keyStates{}
	{

	}


	bool PlayerInputComponent::Update(float l_lastFrameElapsedTime)
	{
		
		m_keyStates.fill(false);

		ProcessKeyboardInput();
		ProcessMouseInput();

		return true;

	}


	void PlayerInputComponent::ProcessKeyboardInput()
	{	

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

	}

	void PlayerInputComponent::ProcessMouseInput()
	{

	}

	const std::array<bool, 4>& PlayerInputComponent::GetKeyStates() const
	{
		return m_keyStates;
	}

}