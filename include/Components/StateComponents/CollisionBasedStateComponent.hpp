#pragma once





#include "Components/StateComponent.hpp"



namespace Asteroid
{


	class CollisionBasedStateComponent : public StateComponent
	{

	public:

		CollisionBasedStateComponent(EntityHandle l_ownerEntityHandle, const uint32_t l_totalNumFrames);

		bool Update(UpdateComponents& l_updateContext) override;

		bool GetCollisionState() const;

		void StartCollisionDeactivation();

		void ResetCollisionState();

	private:

		bool m_collisionActivated{ true };
		bool m_startFrameCount{false};
		const uint32_t m_totalNumFrames;
		uint32_t m_currentFrame{};

	};

}