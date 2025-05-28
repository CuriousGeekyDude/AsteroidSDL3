


#include "Systems/EntityConnector.hpp"
#include "Entities/Entity.hpp"
#include "Components/MovementComponent.hpp"
#include "Engine.hpp"

#include "Systems/LogSystem.hpp"

namespace Asteroid
{

	EntityConnector::EntityConnector(Engine* l_engine)
		:m_engine(l_engine)
	{
		m_frequentlyUsedEntityIndices.reserve(m_totalNumCachedIndices);
	}


	const glm::vec2& EntityConnector::RequestPositionFromPlayer()
	{
		const auto& lv_entities = m_engine->GetEntities();
		if (m_frequentlyUsedEntityIndices.size() > (uint32_t)CachedEntityIndices::PLAYER_ID) {
			const auto& lv_player = lv_entities[m_frequentlyUsedEntityIndices[(uint32_t)CachedEntityIndices::PLAYER_ID]];
			return lv_player.GetCurrentPos();
		}
		else {

			for (auto& l_entity : lv_entities) {
				
				if (EntityType::PLAYER == l_entity.GetType()) {
					m_frequentlyUsedEntityIndices.push_back(l_entity.GetID());
					return l_entity.GetCurrentPos();
				}
			}

		}


		std::runtime_error("Player is not present amongst the entities");


	}


	const glm::vec2& EntityConnector::RequestSpeedFromPlayer()
	{
		const auto& lv_entities = m_engine->GetEntities();

		if (m_frequentlyUsedEntityIndices.size() > (uint32_t)CachedEntityIndices::PLAYER_ID) {
			const auto& lv_player = lv_entities[m_frequentlyUsedEntityIndices[(uint32_t)CachedEntityIndices::PLAYER_ID]];

			MovementComponent* lv_playerMovementComponent = (MovementComponent*)lv_player.GetComponent(ComponentTypes::MOVEMENT);
			return lv_playerMovementComponent->GetSpeed();
		}

		else {
			for (auto& l_entity : lv_entities) {

				if (EntityType::PLAYER == l_entity.GetType()) {
					m_frequentlyUsedEntityIndices.push_back(l_entity.GetID());

					MovementComponent* lv_playerMovementComponent = (MovementComponent*)l_entity.GetComponent(ComponentTypes::MOVEMENT);
					return lv_playerMovementComponent->GetSpeed();
				}
			}
		}

		std::runtime_error("Player is not present amongst the entities");
	}

	float EntityConnector::RequestAngleRotationFromPlayer()
	{

		const auto& lv_entities = m_engine->GetEntities();

		if (m_frequentlyUsedEntityIndices.size() > (uint32_t)CachedEntityIndices::PLAYER_ID) {
			const auto& lv_player = lv_entities[m_frequentlyUsedEntityIndices[(uint32_t)CachedEntityIndices::PLAYER_ID]];

			MovementComponent* lv_playerMovementComponent = (MovementComponent*)lv_player.GetComponent(ComponentTypes::MOVEMENT);
			return lv_playerMovementComponent->GetCurrentAngleOfRotation();
		}

		else {
			for (auto& l_entity : lv_entities) {

				if (EntityType::PLAYER == l_entity.GetType()) {
					m_frequentlyUsedEntityIndices.push_back(l_entity.GetID());
					
					MovementComponent* lv_playerMovementComponent = (MovementComponent*)l_entity.GetComponent(ComponentTypes::MOVEMENT);
					return lv_playerMovementComponent->GetCurrentAngleOfRotation();
				}
			}
		}

		std::runtime_error("Player is not present amongst the entities");

	}

	
}



