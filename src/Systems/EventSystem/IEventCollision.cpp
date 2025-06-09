




#include "Systems/EventSystem/IEventCollision.hpp"




namespace Asteroid
{

	IEventCollision::IEventCollision(Entity* l_entity1
		, Entity* l_entity2
		, CallbacksTimer* l_callbackTimer)
		:m_entity1(l_entity1)
		,m_entity2(l_entity2)
		,m_callbackTimer(l_callbackTimer)
	{

	}


	Entity* IEventCollision::GetEntity1()
	{
		return m_entity1;
	}
	Entity* IEventCollision::GetEntity2()
	{
		return m_entity2;
	}


}