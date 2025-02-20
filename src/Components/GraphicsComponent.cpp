



#include "Components/GraphicsComponent.hpp"


namespace Asteroid
{


	GraphicsComponent::GraphicsComponent(const glm::vec2& l_initialPos, SDL_Texture* l_entityTexture
	,RenderSystem::Renderer* l_renderer, Entity* l_entity)
		:m_entity(l_entity),m_texture(l_entityTexture),
		m_isVisible(true), m_renderer(l_renderer)
	{
	}


}