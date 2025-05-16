#pragma once






#include "Components/AttributeComponent.hpp"



namespace Asteroid
{
	class RayMovementComponent;
	class IndefiniteRepeatableAnimationComponent;

	class CursorAttributeComponent : public AttributeComponent
	{
	public:

		CursorAttributeComponent();


		void Init(EntityHandle l_ownerEntityHandle, uint32_t l_hp, RayMovementComponent* l_movementComp
			, IndefiniteRepeatableAnimationComponent* l_mainAnimComponents);

		bool Update(UpdateComponents& l_updateContext) override;

	private:

		RayMovementComponent* m_movementComponent{};
		IndefiniteRepeatableAnimationComponent* m_mainAnimComponent{};

	};


}