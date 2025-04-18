#pragma once



#include <vector>
#include "EntityHandle.hpp"
#include "Entity.hpp"
#include "EntityType.hpp"



namespace Asteroid
{
	class EntityPool
	{
	private:

		//To mark an entity as active we | with ACTIVE
		// and to mark an entity as inactive we & with INACTIVE
		enum class EntityState : uint32_t
		{
			ACTIVE = 0x80000000,
			INACTIVE = 0x7FFFFFFF
		};

	public:

		EntityPool(const EntityType l_type);

		void Init(const uint32_t l_firstEntityIndex, const uint32_t l_totalNumEntities);

		EntityHandle GetNextInactiveEntityHandle() const;

		void UpdateEntityStates(const std::vector<Entity>& l_entities);
		
		void ResizePool(const uint32_t l_firstEntityIndex, const uint32_t l_totalNumEntities);

	private:
		std::vector<uint32_t> m_entityIndicesAndStates{};

		//The index here is in terms of the index of entity in the
		//entities vector that has all the entities of the game
		uint32_t m_nextInactiveIndex{0U};


		EntityType m_type;

	};
}