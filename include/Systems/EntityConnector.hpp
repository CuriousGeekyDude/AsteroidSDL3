#pragma once


#include <vector>
#include <glm.hpp>
#include "Entities/EntityType.hpp"
#include "Entities/EntityHandle.hpp"

namespace Asteroid
{
	class Entity;
	class Engine;

	class EntityConnector final
	{

	private:

		enum class CachedEntityIndices : uint32_t
		{
			PLAYER_ID = 0,
			FIRST_BULLET_ID
		};

	public:

		EntityConnector(Engine* l_engine);

		const glm::vec2& RequestPositionFromPlayer();
		float RequestAngleRotationFromPlayer();

		const glm::vec2& RequestSpeedFromPlayer();

	private:
		static constexpr uint32_t m_totalNumCachedIndices{32U};
		Engine* m_engine;
		std::vector<uint32_t> m_frequentlyUsedEntityIndices;
	};
}