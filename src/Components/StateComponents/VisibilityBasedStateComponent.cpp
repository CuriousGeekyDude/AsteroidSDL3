




#include "Components/StateComponents/VisibilityBasedStateComponent.hpp"
#include "Components/GraphicsComponent.hpp"
#include "Components/UpdateComponents.hpp"
#include "Engine.hpp"

namespace Asteroid
{

	VisibilityBasedStateComponent::VisibilityBasedStateComponent(EntityHandle l_ownerEntityHandle
		, const GraphicsComponent* l_graphicsComponent)
		:StateComponent(l_ownerEntityHandle)
		,m_graphicsComponent(l_graphicsComponent)
	{

	}

	bool VisibilityBasedStateComponent::Update(UpdateComponents& l_updateContext)
	{
		auto lv_isVisibile = m_graphicsComponent->GetVisibility();

		if (false == lv_isVisibile) {

			auto& lv_ownerEntity = l_updateContext.m_engine->GetEntityFromHandle(m_ownerEntityHandle);
			lv_ownerEntity.SetInactive();

		}

		return true;
	}

}