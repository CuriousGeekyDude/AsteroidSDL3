#pragma once


#include "../MovementComponent.hpp"




namespace Asteroid
{

	class Entity;

	class PlayerMovementComponent : public MovementComponent
	{
	public:

		PlayerMovementComponent(Entity* l_ownerEntity, const InputSystem* l_inputSystem);

		bool Update(float l_deltaTime) override;

	private:

	};

}