#pragma once


#include <glm.hpp>


namespace Asteroid
{
	class Animation;
	class Entity;

	struct CollisionReactionContext final
	{
		Animation* m_animationSystem{};
		Entity* m_ownerEntity{};
	};

}