




#include "Components/PlayerComponents/PlayerGraphicsComponent.hpp"
#include "Components/PlayerComponents/PlayerMovementComponent.hpp"
#include "Systems/RenderingData.hpp"
#include "Engine.hpp"
#include "Components/UpdateComponents.hpp"



namespace Asteroid
{


	PlayerGraphicsComponent::PlayerGraphicsComponent(uint32_t l_textureHandle, EntityHandle l_entityHandle
		,const PlayerMovementComponent* l_playerMovementComponent)
		:GraphicsComponent(l_textureHandle, l_entityHandle)
		,m_playerMovementComponent(l_playerMovementComponent)
	{

	}


	bool PlayerGraphicsComponent::Update(UpdateComponents& l_updateContext)
	{
		glm::ivec2 lv_windowRes{};
		auto& lv_ownerEntity = l_updateContext.m_engine->GetEntityFromHandle(m_ownerEntityHandle);

		l_updateContext.m_engine->GetCurrentWindowSize(lv_windowRes);


		const glm::vec2& lv_currentPos = lv_ownerEntity.GetCurrentPos();
		const float lv_theta = m_playerMovementComponent->GetCurrentAngleOfRotation();

		constexpr int lv_widthToRender{ 90 };
		constexpr int lv_heightToRender{ 90 };
		constexpr float lv_halfWidthToRender{ ((float)lv_widthToRender) / 2.f };
		constexpr float lv_halfHeightToRender{ ((float)lv_heightToRender) / 2.f };


		if (lv_currentPos.x <= -lv_halfWidthToRender || lv_currentPos.x >= ((float)lv_windowRes.x + lv_halfWidthToRender)
			|| lv_currentPos.y >= ((float)lv_windowRes.y + lv_halfHeightToRender) || lv_currentPos.y <= -lv_halfHeightToRender) {
			return true;
		}


		auto* lv_renderer = l_updateContext.m_engine->GetRenderer();

		RenderSystem::RenderingData lv_renderData{};
		lv_renderData.m_widthToRender = lv_widthToRender;
		lv_renderData.m_heightToRender = lv_heightToRender;
		lv_renderData.m_centerOfRotation = glm::vec2{ (float)lv_renderData.m_widthToRender / 2.f, (float)lv_renderData.m_heightToRender / 2.f };
		lv_renderData.m_entityPos = lv_currentPos - lv_renderData.m_centerOfRotation;
		lv_renderData.m_entityTextureHandle = m_textureHandle;
		lv_renderData.m_angleOfRotation = lv_theta;
		lv_renderData.m_centerOfRotation = glm::vec2{ (float)lv_renderData.m_widthToRender/2.f, (float)lv_renderData.m_heightToRender/2.f};

		if (false == lv_renderer->RenderEntity(lv_renderData)) {
			return false;
		}

		return true;


	}

}