#pragma once





#include "Systems/EventSystem/IEventCollision.hpp"
#include "Systems/EventSystem/EventType.hpp"

namespace Asteroid
{
	class CallbacksTimer;

	class EventCollisionBulletPlayer final : public IEventCollision
	{
	public:


		EventCollisionBulletPlayer(Entity* l_entity1
			, Entity* l_entity2
			, CallbacksTimer* l_callbackTimer);



		EventCollisionBulletPlayer(const EventCollisionBulletPlayer&) = delete;
		EventCollisionBulletPlayer& operator=(const EventCollisionBulletPlayer&) = delete;


		EventCollisionBulletPlayer(EventCollisionBulletPlayer&&) = default;
		EventCollisionBulletPlayer& operator=(EventCollisionBulletPlayer&&) = default;


		size_t GetTrueTypeSize() const override;

		EventType GetType() const override;


		std::string GetName() const override;



	private:

		EventType m_type{ 0x8d575432 };



	};


	
}