





#include "Components/OnceRepeatableAnimationComponent.hpp"
#include "Components/UpdateComponents.hpp"
#include "Components/MovementComponent.hpp"
#include "Components/AnimationMetaData.hpp"
#include "Systems/RenderingData.hpp"
#include "Engine.hpp"



namespace Asteroid
{


	OnceRepeatableAnimationComponent::OnceRepeatableAnimationComponent()
	{

	}



	void OnceRepeatableAnimationComponent::Init(const EntityHandle l_entityHandle
		, const AnimationMetaData* l_animationMetaData
		, const MovementComponent* l_movementComponent)
	{
		Component::Init(l_entityHandle);

		m_animationMetaData = l_animationMetaData;
		m_movementComponent = l_movementComponent;
	}



	bool OnceRepeatableAnimationComponent::Update(UpdateComponents& l_updateContext)
	{

		const auto& lv_ownerEntity = l_updateContext.m_engine->GetEntityFromHandle(m_ownerEntityHandle);

		if (false == m_startAnimation) {

			return true;

		}



		if (m_animationMetaData->m_totalNumFrames <= m_currentOffset) {
			m_currentOffset = 0U;
			m_startAnimation = false;
			return true;
		}

		auto* lv_renderer = l_updateContext.m_engine->GetRenderer();
		const float lv_rotationAngleDegrees = m_movementComponent->GetCurrentAngleOfRotation();
		const auto& lv_currentPos = lv_ownerEntity.GetCurrentPos();

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

		return true;

	}

	void OnceRepeatableAnimationComponent::StartAnimation()
	{
		m_startAnimation = true;
	}

}