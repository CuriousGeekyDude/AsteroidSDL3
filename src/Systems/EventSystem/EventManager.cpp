





#include "Systems/EventSystem/EventManager.hpp"
#include "Systems/EventSystem/IEvent.hpp"
#include <stdexcept>
#include "Systems/MemoryAlloc.hpp"


namespace Asteroid
{

	void EventManager::AssociateNewDelegateToEventType(const EventType l_eventType, std::function<void()>&& l_delegate)
	{
		auto lv_eventTypeDelegatesPair = m_eventTypesMappedToTheirDelegates.find(l_eventType);

		if (m_eventTypesMappedToTheirDelegates.end() != lv_eventTypeDelegatesPair) {
			lv_eventTypeDelegatesPair->second.emplace_back(std::move(l_delegate));
		}
		else {
			
			auto lv_newpair = m_eventTypesMappedToTheirDelegates.emplace(l_eventType, std::vector<std::function<void()>>{});
			
			if (false == lv_newpair.second) {
				throw std::runtime_error("Failed to emplace new pair into mapping of event types to their delegates");
			}
			else {
				lv_newpair.first->second.emplace_back(std::move(l_delegate));
			}
		}
	}
	

	void EventManager::AddNewEventToEventQueue(IEvent* l_newEvent)
	{
		auto& lv_currentActiveQueue = m_eventQueues[m_currentActiveQueueIndex];
		auto lv_eventType = l_newEvent->GetType();
		lv_currentActiveQueue.insert(std::pair<EventType, EventType>{lv_eventType, lv_eventType});


	}

	void EventManager::Update(MemoryAlloc& l_allocator)
	{
		auto lv_previousActiveQueueIndex = m_currentActiveQueueIndex;
		m_currentActiveQueueIndex = (m_currentActiveQueueIndex + 1U) % m_totalNumQueues;

		auto& lv_previousActiveQueue = m_eventQueues[lv_previousActiveQueueIndex];

		for (auto lv_event : lv_previousActiveQueue) {

			EventType lv_eventType = lv_event.first;

			auto lv_eventTypeDelegatesPair = m_eventTypesMappedToTheirDelegates.find(lv_eventType);
			
			if (m_eventTypesMappedToTheirDelegates.end() != lv_eventTypeDelegatesPair) {

				for (auto& lv_callbackToExec : lv_eventTypeDelegatesPair->second) {
					lv_callbackToExec();
				}

				m_eventTypesMappedToTheirDelegates.erase(lv_eventTypeDelegatesPair);

			}

		}

		for (auto lv_tempIter = lv_previousActiveQueue.begin(); lv_previousActiveQueue.end() != lv_tempIter;) {
			lv_tempIter = lv_previousActiveQueue.erase(lv_tempIter);
		}

		

	}

	void EventManager::FlushAllEventQueues(MemoryAlloc& l_alloc)
	{
		auto lv_prevQueueIndex = (m_currentActiveQueueIndex + 1U) % m_totalNumQueues;

		auto& lv_currentQueue = m_eventQueues[m_currentActiveQueueIndex];
		auto& lv_prevQueue = m_eventQueues[lv_prevQueueIndex];

		for (auto lv_tempIter = lv_currentQueue.begin(); lv_currentQueue.end() != lv_tempIter;) {
			lv_tempIter = lv_currentQueue.erase(lv_tempIter);
		}

		for (auto lv_tempIter = lv_prevQueue.begin(); lv_prevQueue.end() != lv_tempIter;) {
			lv_tempIter = lv_prevQueue.erase(lv_tempIter);
		}

	}

}