#pragma once




#include "Components/Component.hpp"
#include <glm.hpp>

struct SDL_Texture;

namespace Asteroid
{

	namespace RenderSystem
	{
		class Renderer;
	}

	class Entity;

	class GraphicsComponent : public Component
	{
	public:

		GraphicsComponent(uint32_t l_textureHandle
		, RenderSystem::Renderer* l_renderer, Entity* l_entity);


		virtual ~GraphicsComponent() = default;

	protected:

	protected:
		Entity* m_ownerEntity;
		bool m_isVisible;
		uint32_t m_textureHandle;
		RenderSystem::Renderer* m_renderer;
	};

}