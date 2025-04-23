#pragma once




#include "Components/Component.hpp"
#include <glm.hpp>
#include "Entities/EntityHandle.hpp"

struct SDL_Texture;

namespace Asteroid
{

	namespace RenderSystem
	{
		class Renderer;
	}

	class GraphicsComponent : public Component
	{
	public:

		GraphicsComponent(uint32_t l_textureHandle
		, RenderSystem::Renderer* l_renderer, EntityHandle l_entityHandle
		,const glm::ivec2& l_windowResolution, Engine* l_engine);


		virtual ~GraphicsComponent() = default;

		void SetWindowResolution(const glm::vec2& l_newWindowResol);

	protected:

	protected:
		glm::ivec2 m_windowResolution;
		uint32_t m_textureHandle;
		RenderSystem::Renderer* m_renderer;
	};

}