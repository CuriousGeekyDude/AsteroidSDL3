




#include "Systems/EventSystem/EventCollision.hpp"




namespace Asteroid
{

	EventCollision::EventCollision(Entity* l_entity1
		, Entity* l_entity2
		, CallbacksTimer* l_callbackTimer)
		:m_entity1(l_entity1)
		,m_entity2(l_entity2)
		,m_callbackTimer(l_callbackTimer)
	{

	}


	Entity* EventCollision::GetEntity1()
	{
		return m_entity1;
	}
	Entity* EventCollision::GetEntity2()
	{
		return m_entity2;
	}

	std::string EventCollision::GetName() const
	{
		return std::string{"EventCollision"};
	}

	size_t EventCollision::GetTrueTypeSize() const
	{
		return sizeof(*this);
	}

	EventType EventCollision::GetType() const
	{
		return m_type;
	}
}