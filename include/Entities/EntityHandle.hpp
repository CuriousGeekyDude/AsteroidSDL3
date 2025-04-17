#pragma once


#include <stdint.h>

namespace Asteroid
{
	struct EntityHandle
	{
		EntityHandle() = default;
		EntityHandle(const uint32_t l_handle);
		uint32_t m_entityHandle{};
	};
}