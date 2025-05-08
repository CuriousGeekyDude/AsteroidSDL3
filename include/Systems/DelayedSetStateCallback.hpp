#pragma once




#include <functional>



namespace Asteroid
{

	class StateComponent;

	struct DelayedSetStateCallback final
	{
		std::function<void()> m_callback{};
		uint32_t m_currentFrame{};
		uint32_t m_maxNumFrames{};
	};


}