#pragma once



#include "Entity.hpp"
#include <glm.hpp>
#include <queue>

namespace Asteroid
{

	namespace Physics
	{
		void MovePlayer(Entity& l_player, std::queue<glm::vec2>& l_deltaPosQueue);
		bool IsInView(const Entity& l_entity
			, const int l_widthWindow, const int l_heightWindow
			, const int l_widthTexture, const int l_heightTexture);
	}


}