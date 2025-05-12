#pragma once





#include "Components/AttributeComponent.hpp"
#include "Components/AttributeComponents/AsteroidStates.hpp"


namespace Asteroid
{
	class RayMovementComponent;

	class AsteroidAttributeComponent : public AttributeComponent
	{

	public:

		AsteroidAttributeComponent();


		void Init(EntityHandle l_ownerEntityHandle, uint32_t l_hp, const AsteroidStates l_state, RayMovementComponent* l_rayMovement);


		void SetState(const AsteroidStates l_newState);


		bool Update(UpdateComponents& l_updateContext) override;

	private:

		AsteroidStates m_state{};
		RayMovementComponent* m_rayMovement{};

	};

}