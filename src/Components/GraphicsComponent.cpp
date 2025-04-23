



#include "Components/GraphicsComponent.hpp"


namespace Asteroid
{
	GraphicsComponent::GraphicsComponent(uint32_t l_textureHandle
	,RenderSystem::Renderer* l_renderer, EntityHandle l_entityHandle
	, const glm::ivec2& l_windowResolution, Engine* l_engine)
		:Component(l_entityHandle, l_engine), m_textureHandle(l_textureHandle),
		m_renderer(l_renderer), m_windowResolution(l_windowResolution)
	{
	}


	void GraphicsComponent::SetWindowResolution(const glm::vec2& l_newWindowResol)
	{
		m_windowResolution = l_newWindowResol;
	}

}