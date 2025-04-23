#pragma once


#include "../MovementComponent.hpp"
#include "Entities/EntityHandle.hpp"



namespace Asteroid
{

	class PlayerMovementComponent : public MovementComponent
	{
	public:

		PlayerMovementComponent(EntityHandle l_ownerEntityHandle, Engine* l_engine);

		bool Update(float l_deltaTime) override;

	private:

	};

}