

#include "Engine.hpp"
#include "Utilities/UtilityFunctions.hpp"
#include <iostream>


void FillMeta(Asteroid::AnimationMetaData& l_meta, uint32_t l_firstIndex
	, uint32_t l_totalNumFrames, int l_width, int l_height, Asteroid::AnimationType l_type)
{
	l_meta.m_firstTextureIndex = l_firstIndex;
	l_meta.m_heightToRenderTextures = l_height;
	l_meta.m_widthToRenderTextures = l_width;
	l_meta.m_type = l_type;
	l_meta.m_totalNumFrames = l_totalNumFrames;
}


int main()
{

	using namespace Asteroid;

	try {

	AnimationMetaData lv_meta{};

	EngineInitData lv_engineInitialData;
	lv_engineInitialData.m_animationMetaData.reserve(256U);
	lv_engineInitialData.m_appName = "AsteroidSDL3";
	lv_engineInitialData.m_windowTitle = "Asteroid Game";
	lv_engineInitialData.m_appVersion = "Version 1.0";
	lv_engineInitialData.m_mappedTextureNamesToTheirPaths
		.emplace_back(std::pair<std::string, std::string>("Spaceship", "Assets/DarkRaiderSpaceship.png"));

	FillMeta(lv_meta, 0, 1, 90, 90, AnimationType::MAIN_SPACESHIP);
	lv_engineInitialData.m_animationMetaData.push_back(lv_meta);


	lv_engineInitialData.m_mappedTextureNamesToTheirPaths
		.emplace_back(std::pair<std::string, std::string>("LaserBeam", "Assets/LaserBeam.png"));
	FillMeta(lv_meta, 1, 1, 40, 40, AnimationType::LASER_BEAM);
	lv_engineInitialData.m_animationMetaData.push_back(lv_meta);

	lv_engineInitialData.m_mappedTextureNamesToTheirPaths
		.emplace_back(std::pair<std::string, std::string>("Cursor", "Assets/Cursor.png"));
	FillMeta(lv_meta, 2, 1, 32, 32, AnimationType::CURSOR);
	lv_engineInitialData.m_animationMetaData.push_back(lv_meta);


	lv_engineInitialData.m_mappedTextureNamesToTheirPaths
		.emplace_back(std::pair<std::string, std::string>("BackgroundStarClusters", "Assets/Background.jpg"));
	lv_engineInitialData.m_mappedTextureNamesToTheirPaths
		.emplace_back(std::pair<std::string, std::string>("BackgroundStarClusters2", "Assets/Background2.jpg"));

	lv_engineInitialData.m_animationMetaData.push_back
	(Utilities::ProcessFileOfRelativePathsOfTextures("InitFiles/Animation/ExplosionBombFireAsteroid/RelativePathTextures.txt"
		, lv_engineInitialData.m_mappedTextureNamesToTheirPaths, AnimationType::EXPLOSION_FIRE_ASTEROID
		, 160, 120));
	lv_engineInitialData.m_animationMetaData.push_back
	(Utilities::ProcessFileOfRelativePathsOfTextures("InitFiles/Animation/Asteroid/RelativePathTextures.txt"
		, lv_engineInitialData.m_mappedTextureNamesToTheirPaths, AnimationType::ASTEROID
		, 80, 80));

	lv_engineInitialData.m_animationMetaData.push_back
	(Utilities::ProcessFileOfRelativePathsOfTextures("InitFiles/Animation/WarpEffect/RelativePathTextures.txt"
		, lv_engineInitialData.m_mappedTextureNamesToTheirPaths, AnimationType::WARP_ASTEROID
		, 250, 150));
	

	

		Engine lv_asteroidEngine(std::move(lv_engineInitialData));

		if (false == lv_asteroidEngine.Init()) {
			return -1;
		}

		if (false == lv_asteroidEngine.GameLoop()) {
			return -1;
		}
	}
	catch (const std::runtime_error& l_error) {
		std::cout << l_error.what() << std::endl;
	}
	catch (const std::bad_alloc& l_error) {
		std::cout << l_error.what() << std::endl;
	}
	catch (const std::out_of_range& l_error) {
		std::cout << l_error.what() << std::endl;
	}
	

	return 0;
}