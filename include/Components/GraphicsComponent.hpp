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

		GraphicsComponent(const glm::vec2& l_initialPos, SDL_Texture* l_entityTexture
		, RenderSystem::Renderer* l_renderer, Entity* l_entity);


		virtual ~GraphicsComponent() = default;

	protected:

	protected:
		Entity* m_entity;
		bool m_isVisible;
		SDL_Texture* m_texture;
		RenderSystem::Renderer* m_renderer;
	};

}