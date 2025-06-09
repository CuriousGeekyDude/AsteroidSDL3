





#include "Systems/EventSystem/Events/EventCollisionAsteroidAsteroid.hpp"





namespace Asteroid
{

	EventCollisionAsteroidAsteroid::EventCollisionAsteroidAsteroid(Entity* l_entity1
		, Entity* l_entity2
		, CallbacksTimer* l_callbackTimer)
		:IEventCollision(l_entity1, l_entity2, l_callbackTimer)
	{

	}

	size_t EventCollisionAsteroidAsteroid::GetTrueTypeSize() const
	{
		return sizeof(*this);
	}

	EventType EventCollisionAsteroidAsteroid::GetType() const
	{
		return m_type;
	}


	std::string EventCollisionAsteroidAsteroid::GetName() const
	{
		return "EventCollisionAsteroidAsteroid";
	}

}