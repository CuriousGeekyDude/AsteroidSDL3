



#include "Entities/EntityPool.hpp"

#define LOGGING
#include "Systems/LogSystem.hpp"



namespace Asteroid
{
	EntityPool::EntityPool(const EntityType l_type)
		:m_type(l_type)
	{

	}

	void EntityPool::Init(const uint32_t l_firstEntityIndex, const uint32_t l_totalNumEntities)
	{
		m_entityIndicesAndStates.resize(l_totalNumEntities);
		m_nextInactiveIndex = l_firstEntityIndex;

		for (uint32_t i = 0; i < l_totalNumEntities; ++i) {
			m_entityIndicesAndStates[i] = i + l_firstEntityIndex;
			m_entityIndicesAndStates[i] &= (uint32_t)EntityState::INACTIVE;
		}

	}

	EntityHandle EntityPool::GetNextInactiveEntityHandle() const
	{
		using namespace LogSystem;

		if (UINT32_MAX == m_nextInactiveIndex) {
			LOG(Severity::WARNING, Channel::PROGRAM_LOGIC, "The pool ran out of entities to provide you with. Allocate more entities and resize.\n");
		}
		
		return EntityHandle(m_nextInactiveIndex);
	}

	void EntityPool::ResizePool(const uint32_t l_firstEntityIndex, const uint32_t l_totalNumEntities)
	{
		uint32_t lv_oldSize = (uint32_t)m_entityIndicesAndStates.size();
		m_entityIndicesAndStates.resize(l_totalNumEntities + lv_oldSize);

		for (uint32_t i = 0; i < (uint32_t)m_entityIndicesAndStates.size(); ++i) {

			m_entityIndicesAndStates[i + lv_oldSize] = i + lv_oldSize;
			m_entityIndicesAndStates[i + lv_oldSize] &= (uint32_t)EntityState::INACTIVE;

		}
		m_nextInactiveIndex = l_firstEntityIndex;

	}

	void EntityPool::UpdateEntityStates(const std::vector<Entity>& l_entities)
	{
		if (true == m_entityIndicesAndStates.empty()) {
			return;
		}
		else {
			uint32_t lv_firstIndexOfEntity = m_entityIndicesAndStates[0];

			//To get rid of the last 31st bit
			lv_firstIndexOfEntity &= (uint32_t)EntityState::INACTIVE;

			for (uint32_t i = 0; i < (uint32_t)m_entityIndicesAndStates.size(); ++i) {

				uint32_t lv_currentIndex = i + lv_firstIndexOfEntity;

				if (true == l_entities[lv_currentIndex].IsActive()) {
					m_entityIndicesAndStates[lv_currentIndex] |= (uint32_t)EntityState::ACTIVE;
				}
				else {
					m_entityIndicesAndStates[lv_currentIndex] &= (uint32_t)EntityState::INACTIVE;
				}
			}
		}

		m_nextInactiveIndex = UINT32_MAX;
		for (size_t i = 0; i < m_entityIndicesAndStates.size(); ++i) {
			if ((uint32_t)EntityState::ACTIVE == (m_entityIndicesAndStates[i] & (uint32_t)EntityState::ACTIVE)) {
				continue;
			}
			else {
				m_nextInactiveIndex = ((uint32_t)EntityState::INACTIVE & m_entityIndicesAndStates[i]);
				break;
			}
		}
	}
}