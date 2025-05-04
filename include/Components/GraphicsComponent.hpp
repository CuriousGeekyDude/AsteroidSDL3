#pragma once




#include "Components/Component.hpp"
#include <glm.hpp>

namespace Asteroid
{

	namespace RenderSystem
	{
		class Renderer;
	}


	struct AnimationMetaData;

	//Used to render the entity. This could be a static texture being rendered or an animation.
	//But either way this texture is our main entity. There could be other animations with regards
	//to an event that was triggered in place of the position of our entity. But that requires 
	//another component which we shall define elsewhere.
	class GraphicsComponent : public Component
	{
	public:

		GraphicsComponent(const EntityHandle l_entityHandle
			, const AnimationMetaData* l_animationMetaData);

		virtual bool Update(UpdateComponents& l_updateContext) override;

		virtual ~GraphicsComponent() = default;

	protected:

		const AnimationMetaData* m_animationMetaData{};
		uint32_t m_currentOffset{};
	};

}