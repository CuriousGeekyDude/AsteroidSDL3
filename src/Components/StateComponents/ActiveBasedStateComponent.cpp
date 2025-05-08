





#include "Components/StateComponents/ActiveBasedStateComponent.hpp"
#include "Components/IndefiniteRepeatableAnimationComponent.hpp"
#include "Components/CollisionComponent.hpp"
#include "Components/UpdateComponents.hpp"
#include "Engine.hpp"
#include "Systems/LogSystem.hpp"


namespace Asteroid
{

	ActiveBasedStateComponent::ActiveBasedStateComponent()
	{

	}


	void ActiveBasedStateComponent::Init(EntityHandle l_ownerEntityHandle
		, CollisionComponent* l_collisionComponent
		, IndefiniteRepeatableAnimationComponent* l_repeatableAnimComponent
		, const uint32_t l_frameCountToActivate
		, const uint32_t l_frameCountToDeactivate)
	{
		StateComponent::Init(l_ownerEntityHandle);

		m_collisionComponent = l_collisionComponent;
		m_repeatableAnimationComponent = l_repeatableAnimComponent;
		m_frameCountToActivate = l_frameCountToActivate;
		m_frameCountToDeactivate = l_frameCountToDeactivate;
	}



	uint32_t ActiveBasedStateComponent::GetframeCountToActivate() const
	{
		return m_frameCountToActivate;
	}

	uint32_t ActiveBasedStateComponent::GetframeCountToDeactivate() const
	{
		return m_frameCountToDeactivate;
	}


	bool ActiveBasedStateComponent::Update(UpdateComponents& l_updateContext)
	{
		
		auto& lv_ownerEntity = l_updateContext.m_engine->GetEntityFromHandle(m_ownerEntityHandle);

		if (false == m_repeatableAnimationComponent->IsInWindowBounds() && false == m_delayedActivateCallbackAlreadySet) {
			if (EntityType::PLAYER != lv_ownerEntity.GetType()) {

				lv_ownerEntity.SetActiveState(false);
			}
		}

		return true;
	}

	void ActiveBasedStateComponent::SetDelayedActivationCallbackFlag(const bool l_newValue)
	{
		m_delayedActivateCallbackAlreadySet = l_newValue;
	}


	void ActiveBasedStateComponent::Reset()
	{
		m_delayedActivateCallbackAlreadySet = false;
	}

}