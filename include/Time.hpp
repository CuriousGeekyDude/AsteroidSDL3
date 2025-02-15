#pragma once


#include <cinttypes>

namespace Asteroid
{

	//All times in milliseconds
	struct Time
	{
		uint64_t m_currentTime{};
		uint64_t m_lastFrameElapsedTime{};
	};

}