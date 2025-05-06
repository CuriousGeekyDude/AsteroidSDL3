#pragma once




#include <cinttypes>
#include <string>
#include <SDL3/SDL_video.h>
#include <SDL3/SDL_init.h>
#include <vector>
#include <utility>
#include "Components/AnimationMetaData.hpp"


namespace Asteroid
{
	struct EngineInitData
	{
		std::string m_appName;
		std::string m_appVersion;
		std::string m_windowTitle;
		std::vector<std::pair<std::string, std::string>> m_mappedTextureNamesToTheirPaths;
		std::vector<AnimationMetaData> m_animationMetaData{};
	};
}