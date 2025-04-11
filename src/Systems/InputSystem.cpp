




#include "Systems/InputSystem.hpp"

#define LOGGING
#include "Systems/LogSystem.hpp"
#include <SDL3/SDL_keyboard.h>


namespace Asteroid
{


	const bool* InputSystem::GetKeyStates() const
	{

		return m_keyStatesPressed.data();

	}


	void InputSystem::ProcessKeyboard(const SDL_Event& l_event)
	{
		using namespace LogSystem;

		const bool* lv_keyStates = SDL_GetKeyboardState(nullptr);

		if (nullptr == lv_keyStates) {
			LOG(Severity::FAILURE, Channel::GRAPHICS, "Keyboard state returned is null pointer for the following reason: %s", SDL_GetError());

			//LogSystem::LogCommandLine("Keyboard state returned is null pointer for the following reason: {4}. Exitting....\n", "ERROR", "INPUT-SYSTEM", __LINE__, __FILE__, SDL_GetError());
			exit(EXIT_FAILURE);
		}

		
		memset(m_keyStatesPressed.data(), 0, sizeof(bool)*m_keyStatesPressed.size());
		memset(m_keyStatesUp.data(), 0, sizeof(bool) * m_keyStatesUp.size());

		if (true == lv_keyStates[SDL_SCANCODE_W]) {
			m_keyStatesPressed[(int)Keys::KEY_W] = true;
		}
		if (true == lv_keyStates[SDL_SCANCODE_S]) {
			m_keyStatesPressed[(int)Keys::KEY_S] = true;
		}
		if (true == lv_keyStates[SDL_SCANCODE_D]) {
			m_keyStatesPressed[(int)Keys::KEY_D] = true;
		}
		if (true == lv_keyStates[SDL_SCANCODE_A]) {
			m_keyStatesPressed[(int)Keys::KEY_A] = true;
		}
		if (true == lv_keyStates[SDL_SCANCODE_F1]) {
			m_keyStatesPressed[(int)Keys::KEY_F1] = true;
		}


		if (SDL_EVENT_KEY_UP == l_event.type) {

			if (SDL_SCANCODE_W == l_event.key.scancode) {
				m_keyStatesUp[(int)Keys::KEY_W] = true;
			}
			if (SDL_SCANCODE_S == l_event.key.scancode) {
				m_keyStatesUp[(int)Keys::KEY_S] = true;
			}
			if (SDL_SCANCODE_D == l_event.key.scancode) {
				m_keyStatesUp[(int)Keys::KEY_D] = true;
			}
			if (SDL_SCANCODE_A == l_event.key.scancode) {
				m_keyStatesUp[(int)Keys::KEY_A] = true;
			}
			if (SDL_SCANCODE_F1 == l_event.key.scancode) {
				m_keyStatesUp[(int)Keys::KEY_F1] = true;
			}

		}


	}


	void InputSystem::ProcessInput(const SDL_Event& l_event)
	{

		ProcessKeyboard(l_event);


	}


	bool InputSystem::IsKeyPressed(Keys l_key)
	{
		if (true == m_keyStatesPressed[(int)l_key]) {
			return true;
		}
		return false;
	}

	bool InputSystem::IsKeyUp(const Keys l_key)
	{
		if (true == m_keyStatesUp[(int)l_key]) {
			return true;
		}

		return false;
	}
}