




#include "Components/PlayerComponents/PlayerGraphicsComponent.hpp"
#include "Components/MovementComponent.hpp"
#include "Systems/Renderer.hpp"
#include "Systems/RenderingData.hpp"
#include "Entities/Entity.hpp"


namespace Asteroid
{


	PlayerGraphicsComponent::PlayerGraphicsComponent(const glm::vec2& l_initialPos, SDL_Texture* l_entityTexture
	, MovementComponent* l_movementComponent
	, RenderSystem::Renderer* l_renderer
	,Entity* l_entity)
		:GraphicsComponent(l_initialPos, l_entityTexture, l_renderer, l_entity)
		,m_movementComponent(l_movementComponent)
	{

	}


	bool PlayerGraphicsComponent::Update(float l_lastFrameElapsedTime)
	{
		const auto& lv_transform = m_movementComponent->GetTransform();

		RenderSystem::RenderingData lv_renderData{};
		lv_renderData.m_entityPos = lv_transform 
			* glm::vec3{ m_entity->GetInitialPos().x, m_entity->GetInitialPos().y,1.f};
		lv_renderData.m_entityTexture = m_texture;

		if (false == m_renderer->RenderEntity(lv_renderData)) {
			return false;
		}

		return true;


	}

}