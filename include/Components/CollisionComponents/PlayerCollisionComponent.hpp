#pragma once






#include "Components/CollisionComponent.hpp"
#include <vector>
#include <utility>


namespace Asteroid
{

	class PlayerAttributeComponent;

	class PlayerCollisionComponent : public CollisionComponent
	{
	public:

		PlayerCollisionComponent();

		bool Update(UpdateComponents& l_updateContext) override;



		void Init(EntityHandle l_ownerEntityHandle
			, const uint32_t l_frameCountToActivateCollision
			, const uint32_t l_frameCountToDeactivateCollision
			, const bool l_isCollisionActive
			, IndefiniteRepeatableAnimationComponent* l_repeatableAnimComponent
			, PlayerAttributeComponent* l_playerAttribComponent
			, const uint32_t l_frameTimeToFlushRegisteredCollision);


		void CollisionReaction(IEvent* l_collisionEvent) override;


		std::vector<std::pair<uint32_t, bool>> GetAlreadyRegisteredCollisionIDs() const;
		   

		void SetAlreadyRegisteredCollisionIDs(const std::vector<std::pair<uint32_t, bool>>& l_registeredCollisions);

	private:

		PlayerAttributeComponent* m_attribComponent{};
		uint32_t m_frameTimeToFlushRegisteredCollisionIDs{};
		std::vector<std::pair<uint32_t, bool>> m_alreadyRegisteredCollisionEntityIDs;
	};


}