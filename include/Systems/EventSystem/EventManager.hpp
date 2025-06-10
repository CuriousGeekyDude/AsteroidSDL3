#pragma once



#include <functional>
#include <vector>
#include <unordered_map>
#include <array>
#include "Systems/EventSystem/EventType.hpp"


namespace Asteroid
{

	class IEvent;
	class MemoryAlloc;

	class EventManager final
	{
		static constexpr uint32_t m_totalNumQueues{ 2U };

		typedef std::unordered_map<EventType, std::vector<std::function<void()>>> EventTypesMappedToDelegates;
		typedef std::array<std::unordered_map<EventType,EventType>, m_totalNumQueues> EventQueues;

	public:

		EventManager() = default;
		EventManager(const EventManager&) = delete;
		EventManager(EventManager&&) = default;

		EventManager& operator=(const EventManager&) = delete;
		EventManager& operator=(EventManager&&) = default;

		void AssociateNewDelegateToEventType(const EventType l_eventType, std::function<void()>&& l_delegate);

		void AddNewEventToEventQueue(IEvent* l_newEvent);

		void Update(MemoryAlloc& l_allocator);

		void FlushAllEventQueues(MemoryAlloc& l_allocator);


	private:

		EventTypesMappedToDelegates m_eventTypesMappedToTheirDelegates{};
		EventQueues m_eventQueues{};
		uint32_t m_currentActiveQueueIndex{};
	};

}