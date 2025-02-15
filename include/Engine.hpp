#pragma once



#include "EngineInitData.hpp"
#include "Entity.hpp"
#include "Time.hpp"
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

		//void HandleKeyboardInput(const SDL_Event& l_event);



	private:

		EngineInitData m_initialData;

		std::queue<glm::vec2> m_playerDeltaPosQueue;

		std::vector<Entity> m_entities;

		Time m_timeTracker;

		SDL_Renderer* m_renderer;
		SDL_Window* m_window;
	};


}