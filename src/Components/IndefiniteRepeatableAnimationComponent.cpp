



#include "Components/IndefiniteRepeatableAnimationComponent.hpp"
#include "Components/UpdateComponents.hpp"
#include "Components/MovementComponent.hpp"
#include "Components/StateComponents/ActiveBasedStateComponent.hpp"
#include "Components/AnimationMetaData.hpp"
#include "Systems/RenderingData.hpp"
#include "Engine.hpp"

namespace Asteroid
{
	IndefiniteRepeatableAnimationComponent::IndefiniteRepeatableAnimationComponent()
	{
	}


	void IndefiniteRepeatableAnimationComponent::Init(const EntityHandle l_entityHandle
		, const AnimationMetaData* l_animationMetaData
		, const MovementComponent* l_movementComponent
		, ActiveBasedStateComponent* l_activeStateComponent
		, const uint32_t l_frameCountToActivateVisibility
		, const uint32_t l_frameCountToDeactivateVisibility
		, const bool l_visibleState)
	{
		Component::Init(l_entityHandle);

		m_animationMetaData = l_animationMetaData;
		m_movementComponent = l_movementComponent;
		m_activeStateComponent = l_activeStateComponent;
		m_frameCountToActivateVisibility = l_frameCountToActivateVisibility;
		m_frameCountToDeactivateVisibility = l_frameCountToDeactivateVisibility;
		m_isVisible = l_visibleState;
	}


	bool IndefiniteRepeatableAnimationComponent::GetVisibility() const
	{
		return m_isVisible;
	}

	void IndefiniteRepeatableAnimationComponent::SetVisibleState(const bool l_visibleState)
	{
		m_isVisible = l_visibleState;
	}


	
	bool IndefiniteRepeatableAnimationComponent::IsInWindowBounds() const
	{
		return m_isInWindowBound;
	}


	bool IndefiniteRepeatableAnimationComponent::Update(UpdateComponents& l_updateContext)
	{

		const auto& lv_entity = l_updateContext.m_engine->GetEntityFromHandle(m_ownerEntityHandle);

		glm::ivec2 lv_currentWindowSize{};
		l_updateContext.m_engine->GetCurrentWindowSize(lv_currentWindowSize);

		glm::ivec2 lv_entityDimensions{
		m_animationMetaData->m_widthToRenderTextures
		,m_animationMetaData->m_heightToRenderTextures
		};


		const float lv_halfWidthEntityDim{ (lv_entityDimensions.x) / 2.f };
		const float lv_halfHeightEntityDim{ (lv_entityDimensions.y) / 2.f };

		const auto& lv_currentPos = lv_entity.GetCurrentPos();

		m_isInWindowBound = !(lv_currentPos.x <= -lv_halfWidthEntityDim || lv_currentPos.x >= ((float)lv_currentWindowSize.x + lv_halfWidthEntityDim)
			|| lv_currentPos.y >= ((float)lv_currentWindowSize.y + lv_halfHeightEntityDim) || lv_currentPos.y <= -lv_halfHeightEntityDim);



		if (false == lv_entity.GetActiveState() || (false == m_isVisible && EntityType::PLAYER != lv_entity.GetType())) {
			return true;
		}
		else {
			
			if (false == m_isInWindowBound) {
				
				m_isVisible = false;
				return true;
			}
			else {
				m_isVisible = true;
			}


			auto* lv_renderer = l_updateContext.m_engine->GetRenderer();
			const float lv_rotationAngleDegrees = m_movementComponent->GetCurrentAngleOfRotation();

			RenderSystem::RenderingData lv_renderData{};
			lv_renderData.m_widthToRender = m_animationMetaData->m_widthToRenderTextures;
			lv_renderData.m_heightToRender = m_animationMetaData->m_heightToRenderTextures;
			lv_renderData.m_centerOfRotation = glm::vec2{ (float)lv_renderData.m_widthToRender / 2.f, (float)lv_renderData.m_heightToRender / 2.f };
			lv_renderData.m_entityPos = lv_currentPos - lv_renderData.m_centerOfRotation;
			lv_renderData.m_entityTextureHandle = m_animationMetaData->m_firstTextureIndex + m_currentOffset;
			lv_renderData.m_angleOfRotation = lv_rotationAngleDegrees;
			lv_renderData.m_centerOfRotation = glm::vec2{ (float)lv_renderData.m_widthToRender / 2.f, (float)lv_renderData.m_heightToRender / 2.f };

			if (false == lv_renderer->RenderEntity(lv_renderData)) {
				return false;
			}



			m_currentOffset += 1U;
			m_currentOffset = m_currentOffset % m_animationMetaData->m_totalNumFrames;

		}

		return true;

	}

	void IndefiniteRepeatableAnimationComponent::Reset()
	{
		m_isInWindowBound = true;
	}

}