#pragma once


#include "Components/MovementComponent.hpp"



namespace Asteroid
{

	class PlayerMovementComponent : public MovementComponent
	{
	public:

		PlayerMovementComponent(EntityHandle l_ownerEntityHandle);

		bool Update(UpdateComponents& l_updateContext) override;

	private:

	};

}