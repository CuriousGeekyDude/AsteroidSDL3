




#include "Components/PlayerComponents/PlayerGraphicsComponent.hpp"
#include "Components/PlayerComponents/PlayerMovementComponent.hpp"
#include "Systems/Renderer.hpp"
#include "Systems/RenderingData.hpp"
#include "Entities/Entity.hpp"


namespace Asteroid
{


	PlayerGraphicsComponent::PlayerGraphicsComponent(uint32_t l_textureHandle
	, PlayerMovementComponent* l_movementComponent
	, RenderSystem::Renderer* l_renderer
	,Entity* l_ownerEntity)
		:GraphicsComponent(l_textureHandle, l_renderer, l_ownerEntity)
		,m_movementComponent(l_movementComponent)
	{

	}


	bool PlayerGraphicsComponent::Update(float l_deltaTime)
	{
		const auto& lv_transform = m_movementComponent->GetTransform();
		const glm::vec2& lv_entityInitialPos = m_ownerEntity->GetInitialPos();
		RenderSystem::RenderingData lv_renderData{};
		lv_renderData.m_entityPos = lv_transform 
			* glm::vec3{ lv_entityInitialPos.x, lv_entityInitialPos.y,1.f};
		lv_renderData.m_entityTextureHandle = m_textureHandle;

		if (false == m_renderer->RenderEntity(lv_renderData)) {
			return false;
		}

		return true;


	}

}