


#include "Systems/EntityConnector.hpp"
#include "Entities/Entity.hpp"
#include <limits>


namespace Asteroid
{

	EntityConnector::EntityConnector(const std::vector<Entity>& l_entities)
		:m_entities(l_entities)
	{
		m_frequentlyUsedEntityIndices.reserve(m_totalNumCachedIndices);
	}


	const glm::vec2& EntityConnector::RequestPositionFromPlayer()
	{

		if (m_frequentlyUsedEntityIndices.size() > (uint32_t)CachedEntityIndices::PLAYER_ID) {
			const auto& lv_player = m_entities[m_frequentlyUsedEntityIndices[(uint32_t)CachedEntityIndices::PLAYER_ID]];
			return lv_player.GetCurrentPos();
		}
		else {

			for (auto& l_entity : m_entities) {
				
				if (EntityType::PLAYER == l_entity.GetType()) {
					m_frequentlyUsedEntityIndices.push_back(l_entity.GetID());
					l_entity.GetCurrentPos();
				}
			}

		}

	}
}



