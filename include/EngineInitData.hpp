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
		uint32_t m_width{(uint32_t)512};
		uint32_t m_height{ (uint32_t)512 };
		SDL_WindowFlags m_windowFlags{SDL_WINDOW_RESIZABLE};
		SDL_InitFlags m_sdlInitFlags{SDL_INIT_VIDEO};
		std::unordered_map<std::string, std::string> m_mappedTextureNamesToTheirPaths;
		std::string m_appName;
		std::string m_appVersion;
		std::string m_windowTitle;
	};
}