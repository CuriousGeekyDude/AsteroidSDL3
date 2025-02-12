#pragma once



#include "EngineInitData.hpp"

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

	protected:




	private:

		EngineInitData m_initialData;

		SDL_Renderer* m_renderer;
		SDL_Window* m_window;
	};


}