


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

		bool IsInView(const Entity& l_entity
			,const int l_widthWindow, const int l_heightWindow
			,const int l_widthTexture, const int l_heightTexture)
		{

			glm::vec2 lv_maxPointRec{l_entity.m_data.m_pos.x + l_widthTexture
				, l_entity.m_data.m_pos.y+l_heightTexture};

			if (l_widthWindow <= l_entity.m_data.m_pos.x
				|| l_heightWindow <= l_entity.m_data.m_pos.y) {
				return false;
			}

			if (lv_maxPointRec.x <= 0 || lv_maxPointRec.y <= 0) {
				return false;
			}

			return true;
		}
	}
}