#pragma once


#include "Components/MovementComponent.hpp"



namespace Asteroid
{

	class UserInputBasedMovementComponent : public MovementComponent
	{
	public:

		UserInputBasedMovementComponent(EntityHandle l_ownerEntityHandle);

		bool Update(UpdateComponents& l_updateContext) override;

	private:

	};

}