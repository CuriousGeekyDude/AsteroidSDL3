




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
	,Entity* l_ownerEntity)
		:GraphicsComponent(l_textureHandle, l_renderer, l_ownerEntity)
	{

	}


	bool PlayerGraphicsComponent::Update(float l_deltaTime)
	{
		const glm::vec2& lv_currentPos = m_ownerEntity->GetCurrentPos();

		RenderSystem::RenderingData lv_renderData{};
		lv_renderData.m_entityPos = lv_currentPos;
		lv_renderData.m_entityTextureHandle = m_textureHandle;
		lv_renderData.m_widthToRender = 90;
		lv_renderData.m_heightToRender = 90;

		if (false == m_renderer->RenderEntity(lv_renderData)) {
			return false;
		}

		return true;


	}

}