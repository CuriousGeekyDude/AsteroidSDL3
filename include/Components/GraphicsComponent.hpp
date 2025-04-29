#pragma once




#include "Components/Component.hpp"
#include <glm.hpp>


namespace Asteroid
{

	namespace RenderSystem
	{
		class Renderer;
	}

	class GraphicsComponent : public Component
	{
	public:

		GraphicsComponent(uint32_t l_textureHandle, EntityHandle l_entityHandle);


		virtual ~GraphicsComponent() = default;

	protected:
		uint32_t m_textureHandle{};
	};

}