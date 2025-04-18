#pragma once


#include <vector>
#include <glm.hpp>
#include "Entities/EntityType.hpp"

namespace Asteroid
{
	class Entity;

	class EntityConnector final
	{

	private:

		enum class CachedEntityIndices : uint32_t
		{
			PLAYER_ID = 0,
			FIRST_BULLET_ID
		};

	public:

		EntityConnector(const std::vector<Entity>& l_entities);

		const glm::vec2& RequestPositionFromPlayer();



	private:
		static constexpr uint32_t m_totalNumCachedIndices{32U};
		const std::vector<Entity>& m_entities;
		std::vector<uint32_t> m_frequentlyUsedEntityIndices;
	};
}