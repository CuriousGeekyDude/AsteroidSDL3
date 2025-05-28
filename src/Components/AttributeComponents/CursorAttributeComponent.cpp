




#include "Components/AttributeComponents/CursorAttributeComponent.hpp"
#include "Components/RayMovementComponent.hpp"
#include "Components/UpdateComponents.hpp"
#include "Engine.hpp"
#include "Systems/InputSystem.hpp"
#include "Components/IndefiniteRepeatableAnimationComponent.hpp"





namespace Asteroid
{

	CursorAttributeComponent::CursorAttributeComponent()
	{

	}


	void CursorAttributeComponent::Init(EntityHandle l_ownerEntityHandle, uint32_t l_hp, RayMovementComponent* l_movementComp, IndefiniteRepeatableAnimationComponent* l_mainAnimComponents)
	{
		AttributeComponent::Init(l_ownerEntityHandle, l_hp);

		m_movementComponent = l_movementComp;
		m_mainAnimComponent = l_mainAnimComponents;
	}

	bool CursorAttributeComponent::Update(UpdateComponents& l_updateContext)
	{
		const auto& lv_inputSys = l_updateContext.m_engine->GetInputSystem();

		if (false == lv_inputSys.IsMouseHidden()) {
			m_mainAnimComponent->SetVisibleState(false);
		}
		else {

			auto& lv_ownerEntity = l_updateContext.m_engine->GetEntityFromHandle(m_ownerEntityHandle);

			m_mainAnimComponent->SetVisibleState(true);
			m_mainAnimComponent->SetWindowsBound(true);

			m_movementComponent->SetAngleOfRotation(0.f);
			m_movementComponent->SetRayDirection(glm::vec2{0.f, 0.f});

			lv_ownerEntity.SetCurrentPos(lv_inputSys.GetMousePosRelativeToWindow());
		}


		return true;
	}

}