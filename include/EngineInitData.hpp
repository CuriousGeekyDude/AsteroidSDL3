#pragma once




#include <cinttypes>
#include <string>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_init.h>
#include <unordered_map>


namespace Asteroid
{
	struct EngineInitData
	{
		std::string m_appName;
		std::string m_appVersion;
		std::string m_windowTitle;
		std::unordered_map<std::string, std::string> m_mappedTextureNamesToTheirPaths;
	};
}