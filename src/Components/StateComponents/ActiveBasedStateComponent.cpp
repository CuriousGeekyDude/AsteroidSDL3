





#include "Components/StateComponents/ActiveBasedStateComponent.hpp"
#include "Components/StateComponents/CollisionBasedStateComponent.hpp"
#include "Components/CollisionComponent.hpp"
#include "Components/UpdateComponents.hpp"
#include "Engine.hpp"
#include "Systems/LogSystem.hpp"


namespace Asteroid
{

	ActiveBasedStateComponent::ActiveBasedStateComponent(EntityHandle l_ownerEntityHandle, const uint32_t l_maxNumFrames, const bool l_isActive
		,CollisionComponent* l_collisionComponent
		,CollisionBasedStateComponent* l_collisionStateComp)
		:StateComponent(l_ownerEntityHandle), m_maxNumFrames(l_maxNumFrames)
		,m_isActive(l_isActive)
		,m_collisionComponent(l_collisionComponent)
		,m_collisionStateComponent(l_collisionStateComp)
	{

	}


	bool ActiveBasedStateComponent::Update(UpdateComponents& l_updateContext)
	{
		using namespace LogSystem;

		if (true == m_startFrameCount) {
			
			LOG(Severity::INFO, Channel::PROGRAM_LOGIC, "Frame count down has started for entity with index %u", m_ownerEntityHandle);

			if (m_maxNumFrames == m_frameCount) {

				m_startFrameCount = false;
				m_frameCount = 0U;


				m_isActive = false;

				LOG(Severity::INFO, Channel::PROGRAM_LOGIC, "Entity with index %u is inactivated", m_ownerEntityHandle);

				return true;
			}

			m_frameCount += 1U;
			LOG(Severity::INFO, Channel::PROGRAM_LOGIC, "Frame count %u", m_frameCount);

		}

		return true;
	}

	bool ActiveBasedStateComponent::HasStartedFrameCount() const
	{
		return m_startFrameCount;
	}

	void ActiveBasedStateComponent::StartCount()
	{
		m_startFrameCount = true;
	}

	bool ActiveBasedStateComponent::IsActive() const
	{
		return m_isActive;
	}


	void ActiveBasedStateComponent::SetActiveState(const bool l_state)
	{
		m_isActive = l_state;

		if (nullptr != m_collisionComponent) {
			m_collisionComponent->ResetCollision();
		}


		if (nullptr != m_collisionStateComponent) {
			m_collisionStateComponent->ResetCollisionState();
		}
	}
}