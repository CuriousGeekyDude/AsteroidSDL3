



#include "Components/StateComponents/CollisionBasedStateComponent.hpp"
#include "Systems/LogSystem.hpp"


namespace Asteroid
{

	CollisionBasedStateComponent::CollisionBasedStateComponent(EntityHandle l_ownerEntityHandle, const uint32_t l_totalNumFrames)
		:StateComponent(l_ownerEntityHandle)
		,m_totalNumFrames(l_totalNumFrames)
	{

	}

	bool CollisionBasedStateComponent::Update(UpdateComponents& l_updateContext)
	{

		using namespace LogSystem;


		if (true == m_startFrameCount) {

			if (m_totalNumFrames <= m_currentFrame) {
				m_currentFrame = 0U;
				m_startFrameCount = false;
				m_collisionActivated = false;
				return true;
			}

			LOG(Severity::INFO, Channel::ANIMATION, "Current frame count for collision based state is: %u", m_currentFrame);
			m_currentFrame += 1U;
		}

		return true;
	}

	bool CollisionBasedStateComponent::GetCollisionState() const
	{
		return m_collisionActivated;
	}

	

	void CollisionBasedStateComponent::StartCollisionDeactivation()
	{
		m_startFrameCount = true;
	}

	void CollisionBasedStateComponent::ResetCollisionState()
	{
		m_startFrameCount = false;
		m_collisionActivated = true;
		m_currentFrame = 0U;
	}
}