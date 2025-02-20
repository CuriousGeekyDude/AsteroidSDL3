#pragma once



#include "EngineInitData.hpp"
#include "Entities/Entity.hpp"
#include "Time.hpp"
#include "Systems/GpuResouceManager.hpp"
#include "Systems/Renderer.hpp"

#include <memory>
#include <vector>
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

		void InitEntities();

	private:

		EngineInitData m_initialData;


		std::vector<std::unique_ptr<Entity>> m_entities;

		Time m_trackLastFrameElapsedTime;

		GpuResourceManager m_gpuResourceManager;

		RenderSystem::Renderer m_renderer;

		SDL_Window* m_window;
	};


}