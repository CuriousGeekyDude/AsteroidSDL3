#pragma once







#include "Systems/EventSystem/IEventCollision.hpp"


namespace Asteroid
{

	class CallbacksTimer;

	class EventCollisionAsteroidAsteroid final: public IEventCollision
	{

	public:

		EventCollisionAsteroidAsteroid(Entity* l_entity1
			, Entity* l_entity2
			, CallbacksTimer* l_callbackTimer);


		EventCollisionAsteroidAsteroid(const EventCollisionAsteroidAsteroid&) = delete;
		EventCollisionAsteroidAsteroid& operator=(const EventCollisionAsteroidAsteroid&) = delete;


		EventCollisionAsteroidAsteroid(EventCollisionAsteroidAsteroid&&) = default;
		EventCollisionAsteroidAsteroid& operator=(EventCollisionAsteroidAsteroid&&) = default;

		size_t GetTrueTypeSize() const override;

		EventType GetType() const override;


		std::string GetName() const override;

	private:

		EventType m_type{ 0xbb215702 };
	
	};

}

