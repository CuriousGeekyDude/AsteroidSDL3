




#include "Components/PlayerComponents/PlayerGraphicsComponent.hpp"
#include "Components/PlayerComponents/PlayerMovementComponent.hpp"
#include "Systems/Renderer.hpp"
#include "Systems/RenderingData.hpp"
#include "Entities/Entity.hpp"
#include <SDL3/SDL_log.h>


namespace Asteroid
{


	PlayerGraphicsComponent::PlayerGraphicsComponent(uint32_t l_textureHandle
	, RenderSystem::Renderer* l_renderer
	,Entity* l_ownerEntity
	,const PlayerMovementComponent& l_playerMovementComponent)
		:GraphicsComponent(l_textureHandle, l_renderer, l_ownerEntity)
		,m_playerMovementComponent(&l_playerMovementComponent)
	{

	}


	bool PlayerGraphicsComponent::Update(float l_deltaTime)
	{
		const glm::vec2& lv_currentPos = m_ownerEntity->GetCurrentPos();
		const float lv_theta = m_playerMovementComponent->GetCurrentAngleOfRotation();

		RenderSystem::RenderingData lv_renderData{};
		lv_renderData.m_widthToRender = 90;
		lv_renderData.m_heightToRender = 90;
		lv_renderData.m_centerOfRotation = glm::vec2{ (float)lv_renderData.m_widthToRender / 2.f, (float)lv_renderData.m_heightToRender / 2.f };
		lv_renderData.m_entityPos = lv_currentPos - lv_renderData.m_centerOfRotation;
		lv_renderData.m_entityTextureHandle = m_textureHandle;
		lv_renderData.m_angleOfRotation = lv_theta;
		lv_renderData.m_centerOfRotation = glm::vec2{ (float)lv_renderData.m_widthToRender/2.f, (float)lv_renderData.m_heightToRender/2.f};

		if (false == m_renderer->RenderEntity(lv_renderData)) {
			return false;
		}

		return true;


	}

}