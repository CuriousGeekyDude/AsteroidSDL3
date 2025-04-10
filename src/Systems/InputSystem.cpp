




#include "Systems/InputSystem.hpp"

#define LOGGING
#include "Systems/LogSystem.hpp"
#include <SDL3/SDL_keyboard.h>


namespace Asteroid
{


	const bool* InputSystem::GetKeyStates() const
	{

		return m_keyStates.data();

	}


	void InputSystem::ProcessKeyboard()
	{
		using namespace LogSystem;

		const bool* lv_keyStates = SDL_GetKeyboardState(nullptr);

		if (nullptr == lv_keyStates) {
			LOG(Severity::FAILURE, Channel::GRAPHICS, "Keyboard state returned is null pointer for the following reason: ", SDL_GetError());

			//LogSystem::LogCommandLine("Keyboard state returned is null pointer for the following reason: {4}. Exitting....\n", "ERROR", "INPUT-SYSTEM", __LINE__, __FILE__, SDL_GetError());
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
		if (true == lv_keyStates[SDL_SCANCODE_F1]) {
			m_keyStates[(int)Keys::KEY_F1] = true;
		}


	}


	void InputSystem::ProcessInput()
	{

		ProcessKeyboard();


	}


}