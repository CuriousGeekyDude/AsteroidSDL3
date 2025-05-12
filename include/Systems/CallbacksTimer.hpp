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


	private:

		std::vector<DelayedSetStateCallback> m_delayedSetStateCallbacks{};
	};

}