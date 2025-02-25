#pragma once


#include "../MovementComponent.hpp"




namespace Asteroid
{

	class PlayerInputComponent;

	class PlayerMovementComponent : public MovementComponent
	{
	public:

		PlayerMovementComponent(const PlayerInputComponent* l_playerInputComponent);

		bool Update(float l_deltaTime) override;

	private:
		const PlayerInputComponent* m_playerInputComponent;

	};

}