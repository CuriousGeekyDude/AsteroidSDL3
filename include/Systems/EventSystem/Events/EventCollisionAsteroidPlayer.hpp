#pragma once






#include "Systems/EventSystem/IEventCollision.hpp"


namespace Asteroid
{
	class CallbacksTimer;

	class EventCollisionAsteroidPlayer final : public IEventCollision
	{

	public:


		EventCollisionAsteroidPlayer(Entity* l_entity1
			, Entity* l_entity2
			, CallbacksTimer* l_callbackTimer);


		EventCollisionAsteroidPlayer(const EventCollisionAsteroidPlayer&) = delete;
		EventCollisionAsteroidPlayer& operator=(const EventCollisionAsteroidPlayer&) = delete;


		EventCollisionAsteroidPlayer(EventCollisionAsteroidPlayer&&) = default;
		EventCollisionAsteroidPlayer& operator=(EventCollisionAsteroidPlayer&&) = default;


		size_t GetTrueTypeSize() const override;


		EventType GetType() const override;

		std::string GetName() const override;
		
	private:
		EventType m_type{ 0xe1e5028a };
		
	};
	

}