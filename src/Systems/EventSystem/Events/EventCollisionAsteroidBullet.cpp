





#include "Systems/EventSystem/Events/EventCollisionAsteroidBullet.hpp"



namespace Asteroid
{
	EventCollisionAsteroidBullet::EventCollisionAsteroidBullet(Entity* l_entity1
		, Entity* l_entity2
		, CallbacksTimer* l_callbackTimer)
		: IEventCollision(l_entity1, l_entity2, l_callbackTimer)
	{

	}

	size_t EventCollisionAsteroidBullet::GetTrueTypeSize() const
	{
		return sizeof(*this);
	}

	EventType EventCollisionAsteroidBullet::GetType() const
	{
		return m_type;
	}

	std::string EventCollisionAsteroidBullet::GetName() const
	{
		return "EventCollisionAsteroidBullet";
	}


}