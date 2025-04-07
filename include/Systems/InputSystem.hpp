#pragma once




#include <array>



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
			KEY_D = 3
		};


	public:


		InputSystem() = default;


		const bool* GetKeyStates() const;

		void ProcessInput();

	private:

		void ProcessKeyboard();

	private:
		static constexpr uint32_t m_totalNumInputKeysToProcess{ 4U };
		std::array<bool, m_totalNumInputKeysToProcess> m_keyStates;

	};

}