#pragma once





#include "Systems/EventSystem/IEvent.hpp"
#include "Systems/EventSystem/EventType.hpp"
#include "Entities/EntityHandle.hpp"


namespace Asteroid
{
	class CallbacksTimer;
	class Entity;

	class IEventCollision : public IEvent
	{
	public:

		IEventCollision(Entity* l_entity1
			, Entity* l_entity2
			, CallbacksTimer* l_callbackTimer);


		IEventCollision(const IEventCollision&) = delete;
		IEventCollision& operator=(const IEventCollision&) = delete;

		IEventCollision(IEventCollision&&) = default;
		IEventCollision& operator=(IEventCollision&&) = default;


		Entity* GetEntity1();
		Entity* GetEntity2();

		virtual ~IEventCollision() = default;

	public:

		CallbacksTimer* m_callbackTimer{};

	private:
		Entity* m_entity1;
		Entity* m_entity2;

	};


}