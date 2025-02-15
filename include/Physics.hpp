#pragma once



#include "Entity.hpp"
#include <glm.hpp>
#include <queue>

namespace Asteroid
{

	namespace Physics
	{
		void MovePlayer(Entity& l_player, std::queue<glm::vec2>& l_deltaPosQueue);

	}


}