




#include "Components/StateComponents/VisibilityBasedStateComponent.hpp"
#include "Components/StateComponents/DelayDeactiveBasedStateComponent.hpp"
#include "Components/GraphicsComponent.hpp"
#include "Components/UpdateComponents.hpp"
#include "Engine.hpp"

namespace Asteroid
{

	VisibilityBasedStateComponent::VisibilityBasedStateComponent(EntityHandle l_ownerEntityHandle
		, const GraphicsComponent* l_graphicsComponent
		, const DelayDeactiveBasedStateComponent* l_delayComponent)
		:StateComponent(l_ownerEntityHandle)
		,m_graphicsComponent(l_graphicsComponent)
		, m_delayComponent(l_delayComponent)
	{

	}

	bool VisibilityBasedStateComponent::Update(UpdateComponents& l_updateContext)
	{
		auto lv_isVisibile = m_graphicsComponent->GetVisibility();

		auto& lv_ownerEntity = l_updateContext.m_engine->GetEntityFromHandle(m_ownerEntityHandle);
		
		DelayDeactiveBasedStateComponent* lv_delayComponent = (DelayDeactiveBasedStateComponent*)lv_ownerEntity.GetComponent(ComponentTypes::DELAY_BASED_STATE);
		
		auto lv_isDelayed = lv_delayComponent->HasStartedFrameCount();

		if (false == lv_isVisibile && false == lv_isDelayed) {

			lv_ownerEntity.SetInactive();

		}

		return true;
	}

}