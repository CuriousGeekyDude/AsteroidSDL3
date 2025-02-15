

#include "Engine.hpp"
#include <SDL3/SDL.h>

namespace Asteroid
{
	Engine::Engine(EngineInitData&& l_initialData)
		:m_initialData(std::move(l_initialData))
		,m_renderer(nullptr)
		,m_window(nullptr)
	{
		
	}


	bool Engine::Init()
	{
		if (false == SDL_SetAppMetadata(m_initialData.m_appName.c_str()
			, m_initialData.m_appVersion.c_str(), nullptr)) {
			SDL_Log("SDL Failed to create metadata for the app: %s ", SDL_GetError());
		}

		if (false == SDL_InitSubSystem(m_initialData.m_sdlInitFlags)) {
			SDL_Log("SDL failed to initialize: %s", SDL_GetError());
			return false;
		}

		if (false == SDL_CreateWindowAndRenderer
			(m_initialData.m_windowTitle.c_str()
			, (int)m_initialData.m_width
			, (int)m_initialData.m_height
			, m_initialData.m_windowFlags
			,&m_window, &m_renderer)) {
			
			SDL_Log("SDL failed to create window and renderer: %s", SDL_GetError());
			return false;

		}

		return true;
	}


	bool Engine::GameLoop()
	{

		bool lv_quit = false;

		while (false == lv_quit) {

			SDL_Event lv_event;

			while (true == SDL_PollEvent(&lv_event)) {

				if (SDL_EVENT_QUIT == lv_event.type) {
					lv_quit = true;
				}
			}

			if (false == SDL_SetRenderDrawColor(m_renderer
				, 255, 0, 0, SDL_ALPHA_OPAQUE)) {

				SDL_Log("SDL failed to set the clear color value: %s"
					, SDL_GetError());
				return false;
			}

			if (false == SDL_RenderClear(m_renderer)) {

				SDL_Log("SDL failed to clear the swapchain to the requested color: %s"
					, SDL_GetError());
				return false;
			}

			if (false == SDL_RenderPresent(m_renderer)) {

				SDL_Log("SDL failed to present the swapchain: %s"
					, SDL_GetError());
				return false;
			}

		}

		return true;

	}

	Engine::~Engine()
	{
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
	}
}