#pragma once


#include "Components/MovementComponent.hpp"



namespace Asteroid
{

	class ActiveBasedStateComponent;

	class UserInputBasedMovementComponent : public MovementComponent
	{
	public:

		UserInputBasedMovementComponent();

		bool Update(UpdateComponents& l_updateContext) override;

		void Init(EntityHandle l_ownerEntityHandle);

	private:

	};

}