#pragma once




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

		void ProcessInput(const SDL_Event& l_event);


		bool IsKeyPressed(const Keys l_key);

		bool IsKeyUp(const Keys l_key);

		bool IsMouseButtonPressed(const Mouse l_mouseButton);
		bool IsMouseButtonUp(const Mouse l_mouseButton);

		uint8_t TotalNumConsecutiveRightClicks();
		uint8_t TotalNumConsecutiveLeftClicks();



	private:

		void ProcessKeyboard(const SDL_Event& l_event);
		void ProcessMouse(const SDL_Event& l_event);
		

	private:
		static constexpr uint32_t m_totalNumInputKeysToProcess{ (uint32_t)Keys::KEY_MAXIMUM };
		std::array<bool, m_totalNumInputKeysToProcess> m_keyStatesPressed;
		std::array<bool, m_totalNumInputKeysToProcess> m_keyStatesUp;

		std::array<bool, 2> m_mouseStatesPressed;
		std::array<bool, 2> m_mouseStatesUp;

		//1 means 1 click, 2 means 2 clicks , 3 means 3 clicks, ....
		//But for practical reasons we only record the first 3 consecutive clicks
		uint8_t m_totalNumLeftMouseClicks;


		//1 means 1 click, 2 means 2 clicks , 3 means 3 clicks, ....
		//But for practical reasons we only record the first 3 consecutive clicks
		uint8_t m_totalNumRightMouseClicks;

	};

}