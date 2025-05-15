





#include "Systems/CallbacksTimer.hpp"
#include "Systems/LogSystem.hpp"


namespace Asteroid
{

	CallbacksTimer::CallbacksTimer()
	{
		m_delayedSetStateCallbacks.reserve(1024U);
	}

	void CallbacksTimer::AddSetStateCallback(DelayedSetStateCallback&& l_delayedCallback)
	{
		m_delayedSetStateCallbacks.emplace_back(std::move(l_delayedCallback));
	}

	void CallbacksTimer::Update(const bool l_timeRewinded)
	{

		using namespace LogSystem;

		LOG(Severity::FAILURE, Channel::MEMORY, "Callback timer vector size is %u", (uint32_t)m_delayedSetStateCallbacks.size());

		if (false == l_timeRewinded) {
			for (size_t i = 0U; i < m_delayedSetStateCallbacks.size(); ++i) {

				if (m_delayedSetStateCallbacks[i].m_maxNumFrames == m_delayedSetStateCallbacks[i].m_currentFrame) {
					m_delayedSetStateCallbacks[i].m_callback();
					m_delayedSetStateCallbacks[i].m_currentFrame += 1U;
				}
				else if (m_delayedSetStateCallbacks[i].m_currentFrame < m_delayedSetStateCallbacks[i].m_maxNumFrames) {
					m_delayedSetStateCallbacks[i].m_currentFrame += 1U;
				}
				else {
					std::swap(m_delayedSetStateCallbacks[i], m_delayedSetStateCallbacks.back());
					m_delayedSetStateCallbacks.pop_back();
				}

			}
		}
		else {
			for (size_t i = 0U; i < m_delayedSetStateCallbacks.size(); ++i) {

				if (m_delayedSetStateCallbacks[i].m_maxNumFrames == m_delayedSetStateCallbacks[i].m_currentFrame) {
					--m_delayedSetStateCallbacks[i].m_currentFrame;
				}
				else if (m_delayedSetStateCallbacks[i].m_currentFrame < m_delayedSetStateCallbacks[i].m_maxNumFrames) {
					--m_delayedSetStateCallbacks[i].m_currentFrame;
				}
				else {
					std::swap(m_delayedSetStateCallbacks[i], m_delayedSetStateCallbacks.back());
					m_delayedSetStateCallbacks.pop_back();
				}

			}
		}


	}

	void CallbacksTimer::FlushAllCallbacks()
	{
		m_delayedSetStateCallbacks.resize(0);
	}

}