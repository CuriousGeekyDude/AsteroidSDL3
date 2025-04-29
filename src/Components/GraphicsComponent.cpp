



#include "Components/GraphicsComponent.hpp"
#include "Components/UpdateComponents.hpp"
#include "Components/MovementComponent.hpp"
#include "Systems/RenderingData.hpp"
#include "Engine.hpp"

namespace Asteroid
{
	GraphicsComponent::GraphicsComponent(uint32_t l_textureHandle, EntityHandle l_entityHandle
		, float l_widthToRender, float l_heightToRender
		, const MovementComponent* l_movementComponent)
		:Component(l_entityHandle), m_textureHandle(l_textureHandle)
		,m_widthToRender(l_widthToRender)
		,m_heightToRender(l_heightToRender)
		,m_movementComponent(l_movementComponent)
	{
	}

	bool GraphicsComponent::GetVisibility() const
	{
		return m_isVisible;
	}


	bool GraphicsComponent::Update(UpdateComponents& l_updateContext)
	{
		glm::ivec2 lv_windowRes{};
		auto& lv_ownerEntity = l_updateContext.m_engine->GetEntityFromHandle(m_ownerEntityHandle);

		l_updateContext.m_engine->GetCurrentWindowSize(lv_windowRes);


		const glm::vec2& lv_currentPos = lv_ownerEntity.GetCurrentPos();
		const float lv_thetaDegrees = m_movementComponent->GetCurrentAngleOfRotation();

		const float lv_halfWidthToRender{ (m_widthToRender) / 2.f };
		const float lv_halfHeightToRender{ (m_heightToRender) / 2.f };


		if (lv_currentPos.x <= -lv_halfWidthToRender || lv_currentPos.x >= ((float)lv_windowRes.x + lv_halfWidthToRender)
			|| lv_currentPos.y >= ((float)lv_windowRes.y + lv_halfHeightToRender) || lv_currentPos.y <= -lv_halfHeightToRender) {
			m_isVisible = false;
			return true;
		}
		else {
			m_isVisible = true;
		}



		if (true == m_isVisible) {
			auto* lv_renderer = l_updateContext.m_engine->GetRenderer();

			RenderSystem::RenderingData lv_renderData{};
			lv_renderData.m_widthToRender = m_widthToRender;
			lv_renderData.m_heightToRender = m_heightToRender;
			lv_renderData.m_centerOfRotation = glm::vec2{ (float)lv_renderData.m_widthToRender / 2.f, (float)lv_renderData.m_heightToRender / 2.f };
			lv_renderData.m_entityPos = lv_currentPos - lv_renderData.m_centerOfRotation;
			lv_renderData.m_entityTextureHandle = m_textureHandle;
			lv_renderData.m_angleOfRotation = lv_thetaDegrees;
			lv_renderData.m_centerOfRotation = glm::vec2{ (float)lv_renderData.m_widthToRender / 2.f, (float)lv_renderData.m_heightToRender / 2.f };

			if (false == lv_renderer->RenderEntity(lv_renderData)) {
				return false;
			}
		}

		return true;
	}

}