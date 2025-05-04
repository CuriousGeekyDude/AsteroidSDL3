





#include "Components/StateComponents/DelayDeactiveBasedStateComponent.hpp"
#include "Components/UpdateComponents.hpp"
#include "Engine.hpp"
#include "Systems/LogSystem.hpp"


namespace Asteroid
{

	DelayDeactiveBasedStateComponent::DelayDeactiveBasedStateComponent(EntityHandle l_ownerEntityHandle, const uint32_t l_maxNumFrames)
		:StateComponent(l_ownerEntityHandle), m_maxNumFrames(l_maxNumFrames)
	{

	}


	bool DelayDeactiveBasedStateComponent::Update(UpdateComponents& l_updateContext)
	{
		using namespace LogSystem;

		if (true == m_startFrameCount) {
			
			LOG(Severity::INFO, Channel::PROGRAM_LOGIC, "Frame count down has started for entity with index %u", m_ownerEntityHandle);

			if (m_maxNumFrames == m_frameCount) {

				m_startFrameCount = false;
				m_frameCount = 0U;


				auto& lv_ownerEntity = l_updateContext.m_engine->GetEntityFromHandle(m_ownerEntityHandle);
				lv_ownerEntity.SetInactive();

				LOG(Severity::INFO, Channel::PROGRAM_LOGIC, "Entity with index %u is inactivated", m_ownerEntityHandle);

				return true;
			}

			m_frameCount += 1U;
			LOG(Severity::INFO, Channel::PROGRAM_LOGIC, "Frame count %u", m_frameCount);

		}

		return true;
	}

	bool DelayDeactiveBasedStateComponent::HasStartedFrameCount() const
	{
		return m_startFrameCount;
	}

	void DelayDeactiveBasedStateComponent::StartCount()
	{
		m_startFrameCount = true;
	}
}