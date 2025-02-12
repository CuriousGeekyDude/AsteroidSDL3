#pragma once




#include <cinttypes>
#include <string>


namespace Asteroid
{
	struct EngineInitData
	{
		uint32_t m_width{(uint32_t)512};
		uint32_t m_height{ (uint32_t)512 };
		std::string m_appName;
		std::string m_appVersion;
		std::string m_windowTitle;
	};
}