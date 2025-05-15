





#include "Components/OnceRepeatableAnimationComponent.hpp"
#include "Components/UpdateComponents.hpp"
#include "Components/MovementComponent.hpp"
#include "Components/AnimationMetaData.hpp"
#include "Systems/RenderingData.hpp"
#include "Engine.hpp"
#include "Systems/LogSystem.hpp"



namespace Asteroid
{


	OnceRepeatableAnimationComponent::OnceRepeatableAnimationComponent()
	{

	}



	void OnceRepeatableAnimationComponent::Init(const EntityHandle l_entityHandle
		, const AnimationMetaData* l_animationMetaData
		, const MovementComponent* l_movementComponent
		, const bool l_followEntity)
	{
		Component::Init(l_entityHandle);

		m_animationMetaData = l_animationMetaData;
		m_movementComponent = l_movementComponent;
		m_followEntity = l_followEntity;
	}


	void OnceRepeatableAnimationComponent::Reset()
	{
		m_startAnimation = false;
		m_currentOffset = 0U;
	}

	bool OnceRepeatableAnimationComponent::Update(UpdateComponents& l_updateContext)
	{
		using namespace LogSystem;

		const auto& lv_ownerEntity = l_updateContext.m_engine->GetEntityFromHandle(m_ownerEntityHandle);

		if (false == lv_ownerEntity.GetActiveState()) {
			return true;
		}
		if (false == m_startAnimation) {

			return true;

		}
		else {


			if (m_animationMetaData->m_totalNumFrames <= m_currentOffset) {
				m_currentOffset = 0U;
				m_startAnimation = false;
				return true;
			}

			if (false == m_followEntity && 0U == m_currentOffset) {
				m_initialEntityPos = lv_ownerEntity.GetCurrentPos();
			}

			auto* lv_renderer = l_updateContext.m_engine->GetRenderer();
			const float lv_rotationAngleDegrees = m_movementComponent->GetCurrentAngleOfRotation();
			const auto& lv_currentPos = lv_ownerEntity.GetCurrentPos();

			RenderSystem::RenderingData lv_renderData{};
			lv_renderData.m_widthToRender = m_animationMetaData->m_widthToRenderTextures;
			lv_renderData.m_heightToRender = m_animationMetaData->m_heightToRenderTextures;
			lv_renderData.m_centerOfRotation = glm::vec2{ (float)lv_renderData.m_widthToRender / 2.f, (float)lv_renderData.m_heightToRender / 2.f };
			lv_renderData.m_entityPos = true == m_followEntity ? lv_currentPos - lv_renderData.m_centerOfRotation : m_initialEntityPos - lv_renderData.m_centerOfRotation;
			lv_renderData.m_entityTextureHandle = m_animationMetaData->m_firstTextureIndex + m_currentOffset;
			lv_renderData.m_angleOfRotation = true == m_followEntity ? lv_rotationAngleDegrees : 0.f;
			lv_renderData.m_centerOfRotation = glm::vec2{ (float)lv_renderData.m_widthToRender / 2.f, (float)lv_renderData.m_heightToRender / 2.f };

			LOG(Severity::INFO, Channel::PROGRAM_LOGIC, "animation frame %u.", m_currentOffset);

			if (false == lv_renderer->RenderEntity(lv_renderData)) {

				return false;
			}



			m_currentOffset += 1U;
		}
		return true;

	}



	void OnceRepeatableAnimationComponent::SetCurrentOffset(const uint32_t l_newOffset)
	{
		m_currentOffset = l_newOffset;
	}
	void OnceRepeatableAnimationComponent::SetInitialAnimationPos(const glm::vec2& l_initialEntityPos)
	{
		m_initialEntityPos = l_initialEntityPos;
	}
	void OnceRepeatableAnimationComponent::SetAnimationStartState(const bool l_startAnimation)
	{
		m_startAnimation = l_startAnimation;
	}


	uint32_t OnceRepeatableAnimationComponent::GetCurrentOffset() const
	{
		return m_currentOffset;
	}
	bool OnceRepeatableAnimationComponent::AnimationHasStarted() const
	{
		return m_startAnimation;
	}
	const glm::vec2& OnceRepeatableAnimationComponent::GetInitialAnimationPos() const
	{
		return m_initialEntityPos;
	}


	void OnceRepeatableAnimationComponent::StartAnimation()
	{
		m_startAnimation = true;
	}


	const AnimationMetaData* OnceRepeatableAnimationComponent::GetAnimationMetaData() const
	{
		return m_animationMetaData;
	}

}