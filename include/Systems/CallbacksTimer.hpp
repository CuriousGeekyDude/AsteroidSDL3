#pragma once





#include "Systems/DelayedSetStateCallback.hpp"
#include <vector>


namespace Asteroid
{

	class CallbacksTimer final
	{
	public:

		CallbacksTimer();

		void AddSetStateCallback(DelayedSetStateCallback&& l_delayedCallback);

		void Update(const bool l_timeRewinded);

		void FlushAllCallbacks();


	private:

		std::vector<DelayedSetStateCallback> m_delayedSetStateCallbacks{};
	};

}