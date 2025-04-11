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


	public:


		InputSystem() = default;


		const bool* GetKeyStates() const;

		void ProcessInput(const SDL_Event& l_event);


		bool IsKeyPressed(Keys l_key);

		bool IsKeyUp(const Keys l_key);

	private:

		void ProcessKeyboard(const SDL_Event& l_event);
		

	private:
		static constexpr uint32_t m_totalNumInputKeysToProcess{ (uint32_t)Keys::KEY_MAXIMUM };
		std::array<bool, m_totalNumInputKeysToProcess> m_keyStatesPressed;
		std::array<bool, m_totalNumInputKeysToProcess> m_keyStatesUp;

	};

}