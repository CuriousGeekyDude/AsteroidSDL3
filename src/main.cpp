

#include "Engine.hpp"



int main()
{

	using namespace Asteroid;

	EngineInitData lv_engineInitialData;
	lv_engineInitialData.m_appName = "AsteroidSDL3";
	lv_engineInitialData.m_windowTitle = "Asteroid Game";
	lv_engineInitialData.m_appVersion = "Version 1.0";
	lv_engineInitialData.m_mappedTextureNamesToTheirPaths
		.emplace(std::pair<std::string, std::string>("Spaceship", "Assets/DarkRaiderSpaceship.png"));
	lv_engineInitialData.m_mappedTextureNamesToTheirPaths
		.emplace(std::pair<std::string, std::string>("LaserBeam", "Assets/LaserBeam.png"));


	
	Engine lv_asteroidEngine(std::move(lv_engineInitialData));

	if (false == lv_asteroidEngine.Init()) {
		return -1;
	}

	if (false == lv_asteroidEngine.GameLoop()) {
		return -1;
	}
	

	return 0;
}