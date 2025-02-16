#pragma once



#include "Entity.hpp"
#include <glm.hpp>
#include <queue>

namespace Asteroid
{

	namespace Physics
	{
		void MovePlayer(Entity& l_player, const glm::vec2& l_deltaPos);
		bool IsInView(const Entity& l_entity
			, const int l_widthWindow, const int l_heightWindow
			, const int l_widthTexture, const int l_heightTexture);
	}


}