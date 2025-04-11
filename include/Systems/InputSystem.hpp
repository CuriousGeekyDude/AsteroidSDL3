#pragma once




#include <array>
#include <SDL3/SDL_events.h>


namespace Asteroid
{

	class InputSystem final
	{

	public:

		enum class Keys
		{
			KEY_W = 0,
			KEY_A = 1,
			KEY_S = 2,
			KEY_D = 3,
			KEY_F1 = 4
		};


	public:


		InputSystem() = default;


		const bool* GetKeyStates() const;

		void ProcessInput();


		bool IsKeyPressed(Keys l_key);

		static bool IsKeyUp(const SDL_Event& l_event, SDL_Scancode l_key);

	private:

		void ProcessKeyboard();

	private:
		static constexpr uint32_t m_totalNumInputKeysToProcess{ 5U };
		std::array<bool, m_totalNumInputKeysToProcess> m_keyStates;

	};

}