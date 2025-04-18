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
			KEY_F = 6


			//Maximum number of possible keys. 
			// Not to be used as index into key states.
			KEY_MAXIMUM = 1024,
		};

		enum class Mouse
		{
			LEFT = 0,
			RIGHT = 1
		};

	public:


		InputSystem() = default;


		const bool* GetKeyStates() const;

		void ProcessInput(const SDL_Event& l_event, SDL_Window* l_window);


		bool IsKeyPressed(const Keys l_key);

		bool IsKeyUp(const Keys l_key);

		bool IsMouseButtonPressed(const Mouse l_mouseButton);
		bool IsMouseButtonUp(const Mouse l_mouseButton);

		uint8_t TotalNumConsecutiveRightClicks();
		uint8_t TotalNumConsecutiveLeftClicks();

		const glm::vec2& GetMousePosRelativeToWindow() const;

		bool IsMouseHidden() const;

	private:

		void RegisterKeyboardInputs(const SDL_Event& l_event);
		void RegisterMouseInputs(const SDL_Event& l_event);

		void ProcessMouseInputs(SDL_Window* l_window);
		void ProcessKeyboardInputs(SDL_Window* l_window);
		

	private:
		static constexpr uint32_t m_totalNumInputKeysToProcess{ (uint32_t)Keys::KEY_MAXIMUM };
		std::array<bool, m_totalNumInputKeysToProcess> m_keyStatesPressed;
		std::array<bool, m_totalNumInputKeysToProcess> m_keyStatesUp;

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