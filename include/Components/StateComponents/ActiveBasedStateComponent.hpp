#pragma once






#include "Components/StateComponent.hpp"



namespace Asteroid
{

	class CollisionComponent;
	class CollisionBasedStateComponent;

	class ActiveBasedStateComponent : public StateComponent
	{
	public:

		ActiveBasedStateComponent(EntityHandle l_ownerEntityHandle, const uint32_t l_maxNumFrames, const bool l_isActive
								,CollisionComponent* l_collisionComponent, CollisionBasedStateComponent* l_collisionStateComp);

		bool Update(UpdateComponents& l_updateContext) override;

		bool HasStartedFrameCount() const;

		void StartCount();

		bool IsActive() const;

		void SetActiveState(const bool l_state);

	private:

		bool m_startFrameCount{ false };
		uint32_t m_frameCount{};
		uint32_t m_maxNumFrames{};
		bool m_isActive{ false };

		CollisionComponent* m_collisionComponent{};
		CollisionBasedStateComponent* m_collisionStateComponent{};
	};

}