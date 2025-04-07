




#include "Systems/InputSystem.hpp"
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_log.h>


namespace Asteroid
{


	const bool* InputSystem::GetKeyStates() const
	{

		return m_keyStates.data();

	}


	void InputSystem::ProcessKeyboard()
	{
		const bool* lv_keyStates = SDL_GetKeyboardState(nullptr);

		if (nullptr == lv_keyStates) {
			SDL_Log("\nKeyboard state returned is null pointer. Exitting...\n");
			exit(EXIT_FAILURE);
		}

		
		memset(m_keyStates.data(), 0, sizeof(bool)*m_keyStates.size());

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


	void InputSystem::ProcessInput()
	{

		ProcessKeyboard();


	}


}