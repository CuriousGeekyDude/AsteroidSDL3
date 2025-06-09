#pragma once


#include <string>
#include "Systems/EventSystem/EventType.hpp"

namespace Asteroid
{
	class IEvent
	{
	public:

		IEvent() = default;
		IEvent(const IEvent&) = delete;
		IEvent& operator=(const IEvent&) = delete;
		IEvent(IEvent&&) noexcept = default;
		IEvent& operator=(IEvent&&) noexcept = default;

		virtual std::string GetName() const = 0;

		virtual size_t GetTrueTypeSize() const = 0;

		virtual EventType GetType() const = 0;

		virtual ~IEvent() = default;
		
	};
}