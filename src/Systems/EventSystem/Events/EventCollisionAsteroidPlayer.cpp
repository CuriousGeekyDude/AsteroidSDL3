



#include "Systems/EventSystem/Events/EventCollisionAsteroidPlayer.hpp"



namespace Asteroid
{


	EventCollisionAsteroidPlayer::EventCollisionAsteroidPlayer(Entity* l_entity1
		, Entity* l_entity2
		, CallbacksTimer* l_callbackTimer)
		: IEventCollision(l_entity1, l_entity2, l_callbackTimer)
	{

	}

	size_t EventCollisionAsteroidPlayer::GetTrueTypeSize() const
	{
		return sizeof(*this);
	}

	EventType EventCollisionAsteroidPlayer::GetType() const
	{
		return m_type;
	}

	std::string EventCollisionAsteroidPlayer::GetName() const
	{
		return "EventCollisionAsteroidPlayer";
	}


}