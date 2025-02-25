#pragma once




#include "Components/InputComponent.hpp"
#include <glm.hpp>
#include <array>


namespace Asteroid
{

	class MovementComponent;

	class PlayerInputComponent : public InputComponent
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

		PlayerInputComponent();


		bool Update(float l_lastFrameElapsedTime) override;

		const std::array<bool, 4>& GetKeyStates() const;

	protected:


		void ProcessKeyboardInput();
		void ProcessMouseInput();


	protected:

		std::array<bool, 4> m_keyStates;
	};
}

