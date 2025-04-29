#pragma once




#include "Components/Component.hpp"
#include <glm.hpp>


namespace Asteroid
{

	namespace RenderSystem
	{
		class Renderer;
	}


	class MovementComponent;

	class GraphicsComponent : public Component
	{
	public:

		GraphicsComponent(uint32_t l_textureHandle, EntityHandle l_entityHandle
			, float l_widthToRender, float l_heightToRender
			,const MovementComponent* l_movementComponent);

		bool Update(UpdateComponents& l_updateContext);

		bool GetVisibility() const;

		virtual ~GraphicsComponent() = default;

	protected:
		uint32_t m_textureHandle{};
		float m_widthToRender{};
		float m_heightToRender{};
		bool m_isVisible{ true };
		const MovementComponent* m_movementComponent;
	};

}