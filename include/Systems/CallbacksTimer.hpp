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

		void Update();

		void FlushAllCallbacks();

		const std::vector<DelayedSetStateCallback>& GetDelayedCallbacks() const;
		void SetDelayedCallbacks(const std::vector<DelayedSetStateCallback>& l_delayedCallbacks);


	private:

		std::vector<DelayedSetStateCallback> m_delayedSetStateCallbacks{};
	};

}