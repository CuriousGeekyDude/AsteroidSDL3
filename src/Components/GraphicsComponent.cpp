



#include "Components/GraphicsComponent.hpp"


namespace Asteroid
{


	GraphicsComponent::GraphicsComponent(uint32_t l_textureHandle
	,RenderSystem::Renderer* l_renderer, Entity* l_ownerEntity)
		:m_ownerEntity(l_ownerEntity),m_textureHandle(l_textureHandle),
		m_isVisible(true), m_renderer(l_renderer)
	{
	}


}