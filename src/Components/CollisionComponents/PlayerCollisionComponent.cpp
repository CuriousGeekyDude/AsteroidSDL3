



#include "Components/CollisionComponents/PlayerCollisionComponent.hpp"
#include "Entities/Entity.hpp"
#include "Components/AttributeComponents/PlayerAttributeComponent.hpp"
#include "Components/CollisionComponents/AsteroidCollisionComponent.hpp"
#include "Systems/CallbacksTimer.hpp"
#include "Systems/LogSystem.hpp"
#include "Systems/EventSystem/EventCollision.hpp"


namespace Asteroid
{


	PlayerCollisionComponent::PlayerCollisionComponent()
	{
		m_alreadyRegisteredCollisionEntityIDs.reserve(128U);
	}




	void PlayerCollisionComponent::Init(EntityHandle l_ownerEntityHandle
		, const uint32_t l_frameCountToActivateCollision
		, const uint32_t l_frameCountToDeactivateCollision
		, const bool l_isCollisionActive
		, IndefiniteRepeatableAnimationComponent* l_repeatableAnimComponent
		, PlayerAttributeComponent* l_playerAttribComponent
		, const uint32_t l_frameTimeToFlushRegisteredCollision)
	{
		CollisionComponent::Init(l_ownerEntityHandle, l_frameCountToActivateCollision, l_frameCountToDeactivateCollision, l_isCollisionActive, l_repeatableAnimComponent);

		m_attribComponent = l_playerAttribComponent;
		m_frameTimeToFlushRegisteredCollisionIDs = l_frameTimeToFlushRegisteredCollision;

	}

	bool PlayerCollisionComponent::Update(UpdateComponents& l_updateContext)
	{
		return true;
	}



	void PlayerCollisionComponent::SetAlreadyRegisteredCollisionIDs(const std::vector<std::pair<uint32_t, bool>>& l_registeredCollisions)
	{
		m_alreadyRegisteredCollisionEntityIDs = l_registeredCollisions;
	}



	void PlayerCollisionComponent::CollisionReaction(IEvent* l_collisionEvent)
	{
		using namespace LogSystem;


		EventCollision* lv_collisionEvent = static_cast<EventCollision*>(l_collisionEvent);
		Entity* lv_entityItCollidedWith{};
		Entity* lv_ownerEntity{};

		if (lv_collisionEvent->GetEntity1()->GetID() == m_ownerEntityHandle.m_entityHandle) {
			lv_entityItCollidedWith = lv_collisionEvent->GetEntity2();
			lv_ownerEntity = lv_collisionEvent->GetEntity1();
		}
		else {
			lv_entityItCollidedWith = lv_collisionEvent->GetEntity1();
			lv_ownerEntity = lv_collisionEvent->GetEntity2();
		}


		auto lv_collidedEntityID = lv_entityItCollidedWith->GetID();

		if (EntityType::ASTEROID == lv_entityItCollidedWith->GetType()) {


			for (uint32_t i = 0; i < m_alreadyRegisteredCollisionEntityIDs.size(); ++i) {

				if (lv_collidedEntityID == m_alreadyRegisteredCollisionEntityIDs[i].first) {
					if (true == m_alreadyRegisteredCollisionEntityIDs[i].second) {

						m_attribComponent->DecrementHPByOne();
						
						m_alreadyRegisteredCollisionEntityIDs[i].second = false;

						DelayedSetStateCallback lv_delayedCallback
						{
							.m_callback{[&, i]() {m_alreadyRegisteredCollisionEntityIDs[i].second = true; }},
							.m_maxNumFrames = m_frameTimeToFlushRegisteredCollisionIDs
						};

						lv_collisionEvent->m_callbackTimer->AddSetStateCallback(std::move(lv_delayedCallback));

						return;
					}
					else {
						return;
					}
				}

			}

			m_attribComponent->DecrementHPByOne();

			m_alreadyRegisteredCollisionEntityIDs.push_back(std::pair<uint32_t, bool>(lv_collidedEntityID, false));

			auto lv_size = m_alreadyRegisteredCollisionEntityIDs.size();

			DelayedSetStateCallback lv_delayedCallback
			{
				.m_callback{[&, lv_size]() {m_alreadyRegisteredCollisionEntityIDs[lv_size - 1].second = true; }},
				.m_maxNumFrames = m_frameTimeToFlushRegisteredCollisionIDs
			};

			lv_collisionEvent->m_callbackTimer->AddSetStateCallback(std::move(lv_delayedCallback));

		}

	}


	std::vector<std::pair<uint32_t, bool>> PlayerCollisionComponent::GetAlreadyRegisteredCollisionIDs() const
	{
		return m_alreadyRegisteredCollisionEntityIDs;
	}

}