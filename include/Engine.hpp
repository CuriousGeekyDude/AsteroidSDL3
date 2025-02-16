#pragma once



#include "EngineInitData.hpp"
#include "Entity.hpp"
#include "Time.hpp"
#include "Systems/GpuResouceManager.hpp"
#include <vector>
#include <queue>
#include <glm.hpp>


struct SDL_Window;
struct SDL_Renderer;

namespace Asteroid
{

	class Engine
	{

	public:

		explicit Engine(EngineInitData&& l_initialData);

		bool Init();


		bool GameLoop();


		~Engine();

	private:

		void ProcessKeyboardInput();

		bool ProcessPhysics();

		bool RenderScene();

	private:

		EngineInitData m_initialData;

		std::queue<glm::vec2> m_playerDeltaPosQueue;

		std::vector<Entity> m_entities;

		Time m_trackLastFrameElapsedTime;

		GpuResourceManager m_gpuResourceManager;

		SDL_Renderer* m_renderer;
		SDL_Window* m_window;
	};


}