



#include "Components/GraphicsComponent.hpp"


namespace Asteroid
{
	GraphicsComponent::GraphicsComponent(uint32_t l_textureHandle, EntityHandle l_entityHandle)
		:Component(l_entityHandle), m_textureHandle(l_textureHandle)
	{
	}


}