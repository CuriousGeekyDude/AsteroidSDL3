




#include "Systems/InputSystem.hpp"

#define LOGGING
#include "Systems/LogSystem.hpp"
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_mouse.h>


namespace Asteroid
{


	const bool* InputSystem::GetKeyStates() const
	{

		return m_keyStatesPressed.data();

	}


	void InputSystem::RegisterKeyboardInputs(const SDL_Event& l_event)
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
		if (SDL_SCANCODE_C == l_event.key.scancode) {
			m_keyStatesPressed[(int)Keys::KEY_C] = true;
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
			if (SDL_SCANCODE_C == l_event.key.scancode) {
				m_keyStatesUp[(int)Keys::KEY_C] = true;
			}

		}


	}



	void InputSystem::RegisterMouseInputs(const SDL_Event& l_event)
	{


		memset(m_mouseStatesPressed.data(), 0, sizeof(bool) * m_mouseStatesPressed.size());
		memset(m_mouseStatesUp.data(), 0, sizeof(bool) * m_mouseStatesUp.size());
		m_totalNumLeftMouseClicks = 0;
		m_totalNumRightMouseClicks = 0;

		if (SDL_EVENT_MOUSE_BUTTON_DOWN == l_event.button.type) {
			if (SDL_BUTTON_LEFT == l_event.button.button) {

				m_mouseStatesPressed[(int)Mouse::LEFT] = true;

				if (1 == l_event.button.clicks) {
					m_totalNumLeftMouseClicks = 1;
				}
				else if (2 == l_event.button.clicks) {
					m_totalNumLeftMouseClicks = 2;
				}
				else if (3 == l_event.button.clicks) {
					m_totalNumLeftMouseClicks = 3;
				}
			}
			if (SDL_BUTTON_RIGHT == l_event.button.button) {

				m_mouseStatesPressed[(int)Mouse::RIGHT] = true;

				if (1 == l_event.button.clicks) {
					m_totalNumRightMouseClicks = 1;
				}
				else if (2 == l_event.button.clicks) {
					m_totalNumRightMouseClicks = 2;
				}
				else if (3 == l_event.button.clicks) {
					m_totalNumRightMouseClicks = 3;
				}
			}


			
		}
		if (SDL_EVENT_MOUSE_BUTTON_UP == l_event.button.type) {
			
			if (SDL_BUTTON_LEFT == l_event.button.button) {
				m_mouseStatesUp[(int)Mouse::LEFT] = true;
			}
			if (SDL_BUTTON_RIGHT == l_event.button.button) {
				m_mouseStatesUp[(int)Mouse::RIGHT] = true;
			}
		}

		
		

	}


	void InputSystem::ProcessKeyboardInputs(SDL_Window* l_window)
	{
		using namespace LogSystem;

		if (false == m_mouseHidden && true == m_keyStatesPressed[(int)Keys::KEY_C]) {
			bool lv_result = SDL_SetWindowRelativeMouseMode(l_window ,true);

			if (false == lv_result) {
				LOG(Severity::WARNING, Channel::INPUT, "Failed to hide the cursor due to : %s\n", SDL_GetError());
			}
			m_mouseHidden = lv_result;
		}
	}


	void InputSystem::ProcessMouseInputs(SDL_Window* l_window)
	{
		using namespace LogSystem;

		if (true == m_mouseHidden && 3 == m_totalNumLeftMouseClicks) {
			bool lv_result = SDL_SetWindowRelativeMouseMode(l_window, false);

			if (false == lv_result) {
				LOG(Severity::WARNING, Channel::INPUT, "Failed to show the cursor due to : %s\n", SDL_GetError());
			}

			m_mouseHidden = !lv_result;
		}

		if (true == m_mouseHidden) {
			SDL_GetMouseState(&m_mousePosRelToWindow.x, &m_mousePosRelToWindow.y);
		}
	}

	void InputSystem::ProcessInput(const SDL_Event& l_event, SDL_Window* l_window)
	{

		RegisterKeyboardInputs(l_event);
		RegisterMouseInputs(l_event);

		ProcessKeyboardInputs(l_window);
		ProcessMouseInputs(l_window);

	}


	bool InputSystem::IsKeyPressed(const Keys l_key)
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

	bool InputSystem::IsMouseButtonPressed(const Mouse l_mouseButton)
	{
		if (true == m_mouseStatesPressed[(int)l_mouseButton]) {
			return true;
		}
		return false;
	}
	bool InputSystem::IsMouseButtonUp(const Mouse l_mouseButton)
	{
		if (true == m_mouseStatesUp[(int)l_mouseButton]) {
			return true;
		}
		return false;
	}

	uint8_t InputSystem::TotalNumConsecutiveRightClicks()
	{
		return m_totalNumRightMouseClicks;
	}
	uint8_t InputSystem::TotalNumConsecutiveLeftClicks()
	{
		return m_totalNumLeftMouseClicks;
	}

	const glm::vec2& InputSystem::GetMousePosRelativeToWindow() const
	{
		return m_mousePosRelToWindow;
	}


	bool InputSystem::IsMouseHidden() const
	{
		return m_mouseHidden;
	}
}