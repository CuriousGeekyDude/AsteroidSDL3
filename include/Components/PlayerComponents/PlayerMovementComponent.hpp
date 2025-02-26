#pragma once


#include "../MovementComponent.hpp"




namespace Asteroid
{

	class PlayerInputComponent;
	class Entity;

	class PlayerMovementComponent : public MovementComponent
	{
	public:

		PlayerMovementComponent(const PlayerInputComponent* l_playerInputComponent, Entity* l_ownerEntity);

		bool Update(float l_deltaTime) override;

	private:
		const PlayerInputComponent* m_playerInputComponent;

	};

}