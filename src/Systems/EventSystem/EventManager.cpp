





#include "Systems/EventSystem/EventManager.hpp"
#include "Systems/EventSystem/IEvent.hpp"
#include <stdexcept>
#include "Systems/MemoryAlloc.hpp"


namespace Asteroid
{

	void EventManager::AssociateNewDelegateToEventType(const EventType l_eventType, std::function<void(IEvent*)>&& l_delegate)
	{
		auto lv_eventTypeDelegatesPair = m_eventTypesMappedToTheirDelegates.find(l_eventType);

		if (m_eventTypesMappedToTheirDelegates.end() != lv_eventTypeDelegatesPair) {
			lv_eventTypeDelegatesPair->second.emplace_back(std::move(l_delegate));
		}
		else {
			
			auto lv_newpair = m_eventTypesMappedToTheirDelegates.emplace(l_eventType, std::vector<std::function<void(IEvent*)>>{});
			
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

		lv_currentActiveQueue.push_back(l_newEvent);


	}

	void EventManager::Update(MemoryAlloc& l_allocator)
	{
		auto lv_previousActiveQueueIndex = m_currentActiveQueueIndex;
		m_currentActiveQueueIndex = (m_currentActiveQueueIndex + 1U) % m_totalNumQueues;

		auto& lv_previousActiveQueue = m_eventQueues[lv_previousActiveQueueIndex];

		for (auto lv_event : lv_previousActiveQueue) {

			EventType lv_eventType = lv_event->GetType();

			auto lv_eventTypeDelegatesPair = m_eventTypesMappedToTheirDelegates.find(lv_eventType);
			
			if (m_eventTypesMappedToTheirDelegates.end() != lv_eventTypeDelegatesPair) {

				for (auto& lv_callbackToExec : lv_eventTypeDelegatesPair->second) {
					lv_callbackToExec(lv_event);
				}

				m_eventTypesMappedToTheirDelegates.erase(lv_eventTypeDelegatesPair);

			}
		}


		for (auto l_event : lv_previousActiveQueue) {
			l_allocator.Destruct<IEvent>(l_event, l_event->GetTrueTypeSize());
		}

		lv_previousActiveQueue.resize(0);

	}

}