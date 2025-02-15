

#include "Engine.hpp"
#include "Physics.hpp"
#include <SDL3/SDL.h>
#include "EntityData.hpp"

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

		SDL_Log("Metadata creation was successfull.\n");

		if (false == SDL_InitSubSystem(m_initialData.m_sdlInitFlags)) {
			SDL_Log("SDL failed to initialize at least one of the requested subsystems: %s", SDL_GetError());
			return false;
		}

		SDL_Log("Initialization of all the requested subsystems was successfull.\n");

		if (false == SDL_CreateWindowAndRenderer
			(m_initialData.m_windowTitle.c_str()
			, (int)m_initialData.m_width
			, (int)m_initialData.m_height
			, m_initialData.m_windowFlags
			,&m_window, &m_renderer)) {
			
			SDL_Log("SDL failed to create window and renderer: %s", SDL_GetError());
			return false;

		}

		SDL_Log("Window and renderer creation was successfull.\n");


		SDL_Log("Creating textures on Gpu and their respective entities commencing....\n");
		for (auto& l_mapPairNameToPath : m_initialData.m_mappedTextureNamesToTheirPaths) {
			
			EntityData lv_entityData;
			lv_entityData.m_hasPhysics = true;
			
			if ("Spaceship" == l_mapPairNameToPath.first) {
				lv_entityData.m_isPlayer = true;
			}
			else {
				lv_entityData.m_isPlayer = false;
			}

			lv_entityData.m_pos = glm::vec2{ 0.f, 0.f };
			lv_entityData.m_textureHandle = m_gpuResourceManager.CreateGpuTextureReturnHandle
			(m_renderer, l_mapPairNameToPath.second, l_mapPairNameToPath.first);

			m_entities.push_back(Entity(lv_entityData));
		}


		return true;
	}


	bool Engine::GameLoop()
	{

		bool lv_quit = false;

		while (false == lv_quit) {

			m_timeTracker.m_currentTime = SDL_GetTicks();
			m_timeTracker.m_lastFrameElapsedTime
				= m_timeTracker.m_currentTime - m_timeTracker.m_lastFrameElapsedTime;

			SDL_Event lv_event;

			while (true == SDL_PollEvent(&lv_event)) {

				if (SDL_EVENT_QUIT == lv_event.type) {
					lv_quit = true;
				}

				if (SDL_EVENT_KEY_DOWN == lv_event.type) {
					ProcessKeyboardInput(lv_event);
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



	void Engine::ProcessKeyboardInput(const SDL_Event& l_event)
	{
		glm::vec2 lv_deltaPos{};
		uint64_t lv_speedAmplifier = (uint64_t)1000;

		switch (l_event.key.scancode) {

		case SDL_SCANCODE_W:
			lv_deltaPos.y = (float)(lv_speedAmplifier * m_timeTracker.m_lastFrameElapsedTime);
			break;
		case SDL_SCANCODE_S:
			lv_deltaPos.y = -1.f * (float)(lv_speedAmplifier * m_timeTracker.m_lastFrameElapsedTime);
			break;
		case SDL_SCANCODE_D:
			lv_deltaPos.x = (float)(lv_speedAmplifier * m_timeTracker.m_lastFrameElapsedTime);
			break;
		case SDL_SCANCODE_A:
			lv_deltaPos.x = -1.f * (float)(lv_speedAmplifier * m_timeTracker.m_lastFrameElapsedTime);
			break;

		}

		m_playerDeltaPosQueue.push(lv_deltaPos);
	}


	void Engine::ProcessPhysics()
	{
		using namespace Physics;

		for (auto& l_entity : m_entities) {
			MovePlayer(l_entity, m_playerDeltaPosQueue);
		}
	}


	bool Engine::RenderScene()
	{
		if (false == SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 1)) {
			SDL_Log("SDL failed to set the clear color to the requested color: %s\n", SDL_GetError());
			return false;
		}
		if (false == SDL_RenderClear(m_renderer)) {
			SDL_Log("SDL failed to clear the swapchain with the requested color: %s\n", SDL_GetError());
			return false;
		}

		for (auto& l_entity : m_entities) {
			auto* lv_entityTexture = m_gpuResourceManager.RetrieveGpuTexture(l_entity.m_data.m_textureHandle);
			if (false == SDL_RenderTexture(m_renderer, lv_entityTexture, nullptr, nullptr)) {
				SDL_Log("SDL failed to render a texture: %s\n", SDL_GetError());
				return false;
			}
		}

		if (false == SDL_RenderPresent(m_renderer)) {
			SDL_Log("SDL failed to present the swapchain: %s\n", SDL_GetError());
			return false;
		}

		return true;
	}

	Engine::~Engine()
	{
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
	}
}