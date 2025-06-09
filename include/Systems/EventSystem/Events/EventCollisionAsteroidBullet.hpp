#pragma once





#include "Systems/EventSystem/IEventCollision.hpp"

namespace Asteroid
{

	class CallbacksTimer;

	class EventCollisionAsteroidBullet final : public IEventCollision
	{
	public:

		EventCollisionAsteroidBullet(Entity* l_entity1
			, Entity* l_entity2
			, CallbacksTimer* l_callbackTimer);

		EventType GetType() const override;


		EventCollisionAsteroidBullet(const EventCollisionAsteroidBullet&) = delete;
		EventCollisionAsteroidBullet& operator=(const EventCollisionAsteroidBullet&) = delete;


		EventCollisionAsteroidBullet(EventCollisionAsteroidBullet&&) = default;
		EventCollisionAsteroidBullet& operator=(EventCollisionAsteroidBullet&&) = default;

		size_t GetTrueTypeSize() const override;
	
		std::string GetName() const override;

	private:
		EventType m_type{ 0xe0bb1691 };

	};

}