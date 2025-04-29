#pragma once



#include <vector>
#include "EntityHandle.hpp"
#include "EntityType.hpp"



namespace Asteroid
{

	class Entity;

	class EntityPool
	{

	public:

		EntityPool();

		void Init(const EntityType l_type, const uint32_t l_firstEntityIndex, const uint32_t l_totalNumEntities);

		EntityHandle GetNextInactiveEntityHandle();

		void Update(const std::vector<Entity>& l_entities);

	private:
		//This vector will either have a valid entity index or UINT32_MAX
		std::vector<uint32_t> m_inactiveEntityIndices{};

		//This vector will have only the active indices from the oldest that was activated
		//to the newest one. This is to keep track of which entity index to reuse in case
		//pool runs out of entity indices to return for use in the game.
		std::vector<uint32_t> m_activeEntityIndicesFromOldestToNewest{};

		//The index here is in terms of the index of entity in the
		//entities vector that has all the entities of the game
		uint32_t m_nextInactiveIndex{0U};

		uint32_t m_firstEntityIndex{};

		EntityType m_type{};

	};
}