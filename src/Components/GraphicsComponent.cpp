



#include "Components/GraphicsComponent.hpp"
#include "Components/UpdateComponents.hpp"
#include "Components/MovementComponent.hpp"
#include "Components/StateComponents/ActiveBasedStateComponent.hpp"
#include "Components/AnimationMetaData.hpp"
#include "Components/StateComponents/VisibilityBasedStateComponent.hpp"
#include "Systems/RenderingData.hpp"
#include "Engine.hpp"

namespace Asteroid
{
	GraphicsComponent::GraphicsComponent(const EntityHandle l_entityHandle
		, const AnimationMetaData* l_animationMetaData)
		:Component(l_entityHandle)
		, m_animationMetaData(l_animationMetaData)

	{
	}

	
	bool GraphicsComponent::Update(UpdateComponents& l_updateContext)
	{
		
		const auto& lv_ownerEntity = l_updateContext.m_engine->GetEntityFromHandle(m_ownerEntityHandle);

		MovementComponent* lv_movComponent = (MovementComponent*)lv_ownerEntity.GetComponent(ComponentTypes::MOVEMENT);
		VisibilityBasedStateComponent* lv_visComponent = (VisibilityBasedStateComponent*)lv_ownerEntity.GetComponent(ComponentTypes::VISIBILITY_BASED_STATE);
		ActiveBasedStateComponent* lv_activeComponent = (ActiveBasedStateComponent*)lv_ownerEntity.GetComponent(ComponentTypes::ACTIVE_BASED_STATE);


		if (false == lv_activeComponent->IsActive() || false == lv_visComponent->GetVisibility()) {
			return true;
		}
		

		
		auto* lv_renderer = l_updateContext.m_engine->GetRenderer();
		const auto& lv_entity = l_updateContext.m_engine->GetEntityFromHandle(m_ownerEntityHandle);
		const float lv_rotationAngleDegrees = lv_movComponent->GetCurrentAngleOfRotation();
		const auto& lv_currentPos = lv_entity.GetCurrentPos();

		RenderSystem::RenderingData lv_renderData{};
		lv_renderData.m_widthToRender =	m_animationMetaData->m_widthToRenderTextures;
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

		return true;
	}

}