


#include "Physics.hpp"



namespace Asteroid
{
	namespace Physics
	{
		void MovePlayer(Entity& l_player, std::queue<glm::vec2>& l_deltaPosQueue)
		{
			if (false == l_deltaPosQueue.empty()) {

				if (true == l_player.m_data.m_isPlayer) {

					auto lv_deltaPos = l_deltaPosQueue.front();
					l_deltaPosQueue.pop();

					l_player.m_data.m_pos.x += lv_deltaPos.x;
					l_player.m_data.m_pos.y += lv_deltaPos.y;
				}

			}
		}
	}
}