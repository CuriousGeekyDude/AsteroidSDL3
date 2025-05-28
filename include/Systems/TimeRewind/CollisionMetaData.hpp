#pragma once





#include <vector>
#include <utility>


namespace Asteroid
{


	struct CollisionMetaData final
	{
		std::vector<std::pair<uint32_t, bool>> m_alreadyRegisteredCollisionEntityIDs{};
		uint32_t m_hitBullet{};
		bool m_isCollisionActive{};
		bool m_resetCollision{};
		bool m_firstCollision{};
	};

}