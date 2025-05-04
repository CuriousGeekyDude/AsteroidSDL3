




#include "Components/StateComponents/VisibilityBasedStateComponent.hpp"
#include "Components/StateComponents/ActiveBasedStateComponent.hpp"
#include "Components/AnimationMetaData.hpp"
#include "Components/GraphicsComponent.hpp"
#include "Components/UpdateComponents.hpp"
#include "Engine.hpp"

namespace Asteroid
{

	VisibilityBasedStateComponent::VisibilityBasedStateComponent(EntityHandle l_ownerEntityHandle
		,const AnimationMetaData* l_animationMetaData)
		:StateComponent(l_ownerEntityHandle)
		, m_animationMetaData(l_animationMetaData)
	{

	}

	bool VisibilityBasedStateComponent::Update(UpdateComponents& l_updateContext)
	{
		
		glm::ivec2 lv_currentWindowSize{};
		l_updateContext.m_engine->GetCurrentWindowSize(lv_currentWindowSize);

		glm::ivec2 lv_entityDimensions{
		m_animationMetaData->m_widthToRenderTextures
		,m_animationMetaData->m_heightToRenderTextures
		};
		

		const float lv_halfWidthEntityDim{ (lv_entityDimensions.x) / 2.f };
		const float lv_halfHeightEntityDim{ (lv_entityDimensions.y) / 2.f };
		
		const auto& lv_entity = l_updateContext.m_engine->GetEntityFromHandle(m_ownerEntityHandle);
		const auto& lv_currentPos = lv_entity.GetCurrentPos();


		ActiveBasedStateComponent* lv_activeComponent = (ActiveBasedStateComponent*)lv_entity.GetComponent(ComponentTypes::ACTIVE_BASED_STATE);

		if (false == lv_activeComponent->IsActive()) {
			return true;
		}

		if (lv_currentPos.x <= -lv_halfWidthEntityDim || lv_currentPos.x >= ((float)lv_currentWindowSize.x + lv_halfWidthEntityDim)
			|| lv_currentPos.y >= ((float)lv_currentWindowSize.y + lv_halfHeightEntityDim) || lv_currentPos.y <= -lv_halfHeightEntityDim
			|| true == lv_activeComponent->HasStartedFrameCount()) {
			m_isVisible = false;
			return true;
		}


		return true;
	}


	void VisibilityBasedStateComponent::SetVisibility(const bool l_visibility)
	{
		m_isVisible = l_visibility;
	}

	bool VisibilityBasedStateComponent::GetVisibility() const
	{
		return m_isVisible;
	}

}