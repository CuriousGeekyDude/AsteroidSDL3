#pragma once



#include "EngineInitData.hpp"
#include "Time.hpp"
#include "Systems/GpuResouceManager.hpp"
#include "Systems/Renderer.hpp"
#include "Systems/InputSystem.hpp"

#include <vector>
#include <glm.hpp>


struct SDL_Window;
struct SDL_Renderer;

namespace Asteroid
{

	
	class Entity;

	class Engine
	{

	public:

		explicit Engine(EngineInitData&& l_initialData);

		bool Init();


		bool GameLoop();


		~Engine();

	private:

		void InitEntities();

	private:

		EngineInitData m_initialData;


		std::vector<Entity> m_entities;

		Time m_trackLastFrameElapsedTime;

		RenderSystem::Renderer m_renderer;
		InputSystem m_inputSystem;

		GpuResourceManager m_gpuResourceManager;

		SDL_Window* m_window;
	};


}