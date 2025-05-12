



#include "Entities/EntityPool.hpp"
#include "Entities/Entity.hpp"
#include "Components/StateComponents/ActiveBasedStateComponent.hpp"
#include <utility>
#include <limits>



namespace Asteroid
{
	EntityPool::EntityPool()
	{

	}

	void EntityPool::Init(const EntityType l_type, const uint32_t l_firstEntityIndex, const uint32_t l_totalNumEntities)
	{
		m_inactiveEntityIndices.resize(l_totalNumEntities);
		m_activeEntityIndicesFromOldestToNewest.resize(l_totalNumEntities);
		m_nextInactiveIndex = l_firstEntityIndex;
		m_type = l_type;
		m_firstEntityIndex = l_firstEntityIndex;

		for (uint32_t i = 0; i < l_totalNumEntities; ++i) {
			m_inactiveEntityIndices[i] = i + l_firstEntityIndex;
			m_activeEntityIndicesFromOldestToNewest[i] = std::numeric_limits<uint32_t>::max();
		}

	}

	EntityHandle EntityPool::GetNextInactiveEntityHandle()
	{

		if (std::numeric_limits<uint32_t>::max() == m_nextInactiveIndex) {
			uint32_t lv_firstElement = m_activeEntityIndicesFromOldestToNewest[0];

			for (size_t i = 0; i < m_activeEntityIndicesFromOldestToNewest.size(); ++i) {
				if (m_activeEntityIndicesFromOldestToNewest.size() != (i + 1)) {
					m_activeEntityIndicesFromOldestToNewest[i] = m_activeEntityIndicesFromOldestToNewest[i + 1];
				}
			}

			m_activeEntityIndicesFromOldestToNewest.back() = lv_firstElement;

			return EntityHandle(lv_firstElement);
		}
		else {

			for (size_t i = 0; i < m_activeEntityIndicesFromOldestToNewest.size(); ++i) {
				if (std::numeric_limits<uint32_t>::max() == m_activeEntityIndicesFromOldestToNewest[i]) {
					m_activeEntityIndicesFromOldestToNewest[i] = m_nextInactiveIndex;
					break;
				}
			}

			EntityHandle lv_returnInactiveIndex{m_nextInactiveIndex};
			m_inactiveEntityIndices[m_nextInactiveIndex - m_firstEntityIndex] = std::numeric_limits<uint32_t>::max();
			m_nextInactiveIndex = std::numeric_limits<uint32_t>::max();
			for (size_t i = 0; i < m_inactiveEntityIndices.size(); ++i) {

				if (std::numeric_limits<uint32_t>::max() != m_inactiveEntityIndices[i]) {
					m_nextInactiveIndex = m_inactiveEntityIndices[i];
					break;
				}

			}

			return lv_returnInactiveIndex;
		}

	}


	void EntityPool::Reset()
	{
		m_nextInactiveIndex = m_firstEntityIndex;
		for (uint32_t i = 0; i < (uint32_t)m_inactiveEntityIndices.size(); ++i) {
			m_inactiveEntityIndices[i] = i + m_firstEntityIndex;
			m_activeEntityIndicesFromOldestToNewest[i] = std::numeric_limits<uint32_t>::max();
		}

	}


	uint32_t EntityPool::GetTotalNumInactiveEntities() const
	{
		uint32_t lv_totalNumInactiveEntities{};
		for (const auto l_inactiveIndex : m_inactiveEntityIndices) {
			if (std::numeric_limits<uint32_t>::max() != l_inactiveIndex) {
				++lv_totalNumInactiveEntities;
			}
		}

		return lv_totalNumInactiveEntities;
	}
	uint32_t EntityPool::GetTotalNumActiveEntities() const
	{
		uint32_t lv_totalNumActiveEntities{};
		for (const auto l_inactiveIndex : m_inactiveEntityIndices) {
			if (std::numeric_limits<uint32_t>::max() == l_inactiveIndex) {
				++lv_totalNumActiveEntities;
			}
		}

		return lv_totalNumActiveEntities;
	}

	void EntityPool::Update(const std::vector<Entity>& l_entities)
	{
		if (true == m_inactiveEntityIndices.empty() || true == m_activeEntityIndicesFromOldestToNewest.empty()) {
			return;
		}
		else {

			for (uint32_t i = 0; i < (uint32_t)m_inactiveEntityIndices.size(); ++i) {

				if (true == l_entities[i + m_firstEntityIndex].GetActiveState()) {
					m_inactiveEntityIndices[i] = std::numeric_limits<uint32_t>::max();
				}
				else {
					m_inactiveEntityIndices[i] = i + m_firstEntityIndex;
					m_activeEntityIndicesFromOldestToNewest[i] = std::numeric_limits<uint32_t>::max();
				}
			}
		}

		m_nextInactiveIndex = std::numeric_limits<uint32_t>::max();
		for (size_t i = 0; i < m_inactiveEntityIndices.size(); ++i) {
			
			if (std::numeric_limits<uint32_t>::max() != m_inactiveEntityIndices[i]) {
				m_nextInactiveIndex = m_inactiveEntityIndices[i];
				break;
			}

		}


		//This vector could have the meaningful entity indices and max() interleaved after the updates above.
		//Therefore in order to make sure all meaningful entity indices are adjacent to each other,
		//we scan the whole vector and put them next to each other.
		for (size_t i = 0; i < m_activeEntityIndicesFromOldestToNewest.size(); ++i) {

			if (std::numeric_limits<uint32_t>::max() == m_activeEntityIndicesFromOldestToNewest[i]) {
				for (size_t j = i + 1; j < m_activeEntityIndicesFromOldestToNewest.size(); ++j) {
					if (std::numeric_limits<uint32_t>::max() != m_activeEntityIndicesFromOldestToNewest[j]) {
						m_activeEntityIndicesFromOldestToNewest[i] = m_activeEntityIndicesFromOldestToNewest[j];
						m_activeEntityIndicesFromOldestToNewest[j] = std::numeric_limits<uint32_t>::max();
						break;
					}
				}
			}
		}


	}
}