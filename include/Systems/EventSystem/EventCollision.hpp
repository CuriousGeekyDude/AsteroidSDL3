#pragma once





#include "Systems/EventSystem/IEvent.hpp"
#include "Systems/EventSystem/EventType.hpp"
#include "Entities/EntityHandle.hpp"


namespace Asteroid
{
	class CallbacksTimer;
	class Entity;

	class EventCollision : public IEvent
	{
	public:

		EventCollision(Entity* l_entity1
			, Entity* l_entity2
			, CallbacksTimer* l_callbackTimer);


		EventCollision(const EventCollision&) = delete;
		EventCollision& operator=(const EventCollision&) = delete;

		EventCollision(EventCollision&&) = default;
		EventCollision& operator=(EventCollision&&) = default;


		Entity* GetEntity1();
		Entity* GetEntity2();

		std::string GetName() const override;

		size_t GetTrueTypeSize() const override;

		EventType GetType() const override;

	public:

		CallbacksTimer* m_callbackTimer{};

	private:
		Entity* m_entity1;
		Entity* m_entity2;
		EventType m_type{ 0xe0dcc046 };

	};

}