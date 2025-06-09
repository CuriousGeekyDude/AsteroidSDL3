



#include "Systems/EventSystem/Events/EventCollisionBulletPlayer.hpp"



namespace Asteroid
{

	EventCollisionBulletPlayer::EventCollisionBulletPlayer(Entity* l_entity1
		, Entity* l_entity2
		, CallbacksTimer* l_callbackTimer)
		:IEventCollision(l_entity1, l_entity2, l_callbackTimer)
	{

	}


	EventType EventCollisionBulletPlayer::GetType() const
	{
		return m_type;
	}


	size_t EventCollisionBulletPlayer::GetTrueTypeSize() const
	{
		return sizeof(*this);
	}

	std::string EventCollisionBulletPlayer::GetName() const
	{
		return "EventCollisionBulletPlayer";
	}


}