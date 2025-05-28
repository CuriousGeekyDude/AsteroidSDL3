#pragma once





#include "Systems/TimeRewind/ActiveBasedStateMetaData.hpp"
#include "Systems/TimeRewind/AttributeMetaData.hpp"
#include "Systems/TimeRewind/CollisionMetaData.hpp"
#include "Systems/TimeRewind/EntityMetaData.hpp"
#include "Systems/TimeRewind/IndefiniteRepeatAnimationMetaData.hpp"
#include "Systems/TimeRewind/MovementMetaData.hpp"
#include "Systems/TimeRewind/OnceRepeatAnimationMetaData.hpp"
#include <array>


namespace Asteroid
{

	struct EntityFrameTimeRewind final
	{
		CollisionMetaData m_collisionMetaData{};
		MovementMetaData m_movementMetaData{};
		std::array<OnceRepeatAnimationMetaData, 2> m_onceRepAnimMetaData;
		EntityMetaData m_entityMetaData{};
		AttributeMetaData m_attribMetaData{};
		IndefiniteRepeatAnimationMetaData m_indefRepAnimMetaData{};
		ActiveBasedStateMetaData m_activeMetaData{};
	};

}