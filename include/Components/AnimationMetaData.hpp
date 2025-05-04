#pragma once




#include "Components/AnimationType.hpp"
#include <glm.hpp>

namespace Asteroid
{

	struct AnimationMetaData final
	{
		AnimationType m_type{};
		uint32_t m_firstTextureIndex{};
		uint32_t m_totalNumFrames{};
		int m_widthToRenderTextures{};
		int m_heightToRenderTextures{};
	};

}