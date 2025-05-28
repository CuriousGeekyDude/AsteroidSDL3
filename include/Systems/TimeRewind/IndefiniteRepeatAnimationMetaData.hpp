#pragma once






#include <cinttypes>


namespace Asteroid
{

	struct IndefiniteRepeatAnimationMetaData final
	{
		uint32_t m_currentOffset{};
		bool m_isVisible{};
		bool m_isInWindowBounds{};
	};

}