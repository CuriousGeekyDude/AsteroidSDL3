#pragma once




#include <glm.hpp>
#include <array>
#include <SDL3/SDL_events.h>


namespace Asteroid
{

	class InputSystem final
	{

	public:

		enum class Keys : uint32_t
		{
			KEY_W = 0,
			KEY_A = 1,
			KEY_S = 2,
			KEY_D = 3,
			KEY_F1 = 4,
			KEY_C = 5,
			KEY_F = 6,
			KEY_T = 7,


			//Maximum number of possible keys. 
			// Not to be used as index into key states.
			KEY_MAXIMUM = 1024
		};

		enum class Mouse
		{
			LEFT = 0,
			RIGHT = 1
		};

		enum class KeyStates : uint32_t
		{
			KEY_DOWN_REPETITION_ALLOWED = 0U,
			KEY_UP,


			INVALID
		};

	public:


		InputSystem() = default;


		void ProcessInput(const SDL_Event& l_event, SDL_Window* l_window);


		bool IsNoRepetitionAllowedKeyPressed(const Keys l_key) const;
		bool IsRepetitionAllowedKeyPressed(const Keys l_key) const;
		bool IsKeyUp(const Keys l_key) const;

		bool IsMouseButtonPressed(const Mouse l_mouseButton) const;
		bool IsMouseButtonUp(const Mouse l_mouseButton) const;

		uint8_t TotalNumConsecutiveRightClicks() const;
		uint8_t TotalNumConsecutiveLeftClicks() const;

		const glm::vec2& GetMousePosRelativeToWindow() const;

		void FlushNotAllowedRepetitionKeys();

		bool IsMouseHidden() const;

		void SetMousePos(const glm::vec2& l_mousePos);
		void SetHiddenStateOfMouse(const bool l_isHidden);

	private:

		void RegisterKeyboardInputs(const SDL_Event& l_event);
		void RegisterMouseInputs(const SDL_Event& l_event);

		void ProcessMouseInputs(SDL_Window* l_window);
		void ProcessKeyboardInputs(SDL_Window* l_window);
		

	private:
		static constexpr uint32_t m_totalNumInputKeysToProcess{ (uint32_t)Keys::KEY_MAXIMUM };
		
		std::array<KeyStates, m_totalNumInputKeysToProcess> m_keyStates{};
		std::array<bool, m_totalNumInputKeysToProcess> m_notAllowedRepetitionKeys{};

		std::array<bool, 2> m_mouseStatesPressed;
		std::array<bool, 2> m_mouseStatesUp;

		glm::vec2 m_mousePosRelToWindow{};
		//1 means 1 click, 2 means 2 clicks , 3 means 3 clicks, ....
		//But for practical reasons we only record the first 3 consecutive clicks
		uint8_t m_totalNumLeftMouseClicks;


		//1 means 1 click, 2 means 2 clicks , 3 means 3 clicks, ....
		//But for practical reasons we only record the first 3 consecutive clicks
		uint8_t m_totalNumRightMouseClicks;

		bool m_mouseHidden{ false };

	};

}