

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

			m_trackLastFrameElapsedTime.m_currentTime = SDL_GetTicks();

			SDL_Event lv_event;

			if (true == SDL_PollEvent(&lv_event)) {
				if (SDL_EVENT_QUIT == lv_event.type) {
					lv_quit = true;
				}
			}


			ProcessKeyboardInput();
			if (false == ProcessPhysics()) {
				return false;
			}
			if (false == RenderScene()) {
				return false;
			}

			m_trackLastFrameElapsedTime.m_lastFrameElapsedTime = SDL_GetTicks() - m_trackLastFrameElapsedTime.m_currentTime;
		}

		return true;

	}



	void Engine::ProcessKeyboardInput()
	{
		glm::vec2 lv_deltaPos{};
		float lv_speedDamper = 0.1f;

		const bool* lv_keyStates = SDL_GetKeyboardState(nullptr);


		if (true == lv_keyStates[SDL_SCANCODE_W]) {
			lv_deltaPos.y = -1.f * (float)(lv_speedDamper * m_trackLastFrameElapsedTime.m_lastFrameElapsedTime);
		}
		if (true == lv_keyStates[SDL_SCANCODE_S]) {
			lv_deltaPos.y = (float)(lv_speedDamper * m_trackLastFrameElapsedTime.m_lastFrameElapsedTime);
		}
		if (true == lv_keyStates[SDL_SCANCODE_D]) {
			lv_deltaPos.x = (float)(lv_speedDamper * m_trackLastFrameElapsedTime.m_lastFrameElapsedTime);
		}
		if (true == lv_keyStates[SDL_SCANCODE_A]) {
			lv_deltaPos.x = -1.f * (float)(lv_speedDamper * m_trackLastFrameElapsedTime.m_lastFrameElapsedTime);
		}

		m_playerDeltaPosQueue.push(lv_deltaPos);
	}


	bool Engine::ProcessPhysics()
	{
		using namespace Physics;

		for (auto& l_entity : m_entities) {
			
			int lv_windowWidth{ 0 };
			int lv_windowHeight{0};
			auto* lv_entityGpuTexture = m_gpuResourceManager.RetrieveGpuTexture(l_entity.m_data.m_textureHandle);

			if (nullptr == lv_entityGpuTexture) {
				SDL_Log("Failed to retrive the gpu texture of claimed handle: %d"
					, (int)l_entity.m_data.m_textureHandle);
				return false;
			}

			if (false == SDL_GetWindowSize(m_window, &lv_windowWidth, &lv_windowHeight)) {
				SDL_Log("SDL failed to query the size of the window: %s", SDL_GetError());
				return false;
			}


			if (false == IsInView(l_entity, lv_windowWidth
				, lv_windowHeight, lv_entityGpuTexture->w, lv_entityGpuTexture->h)) {
				l_entity.m_data.m_isVisible = false;
			}
			else {
				l_entity.m_data.m_isVisible = true;
			}

			auto lv_deltaPos = m_playerDeltaPosQueue.front();
			m_playerDeltaPosQueue.pop();
			MovePlayer(l_entity, lv_deltaPos);

			continue;
		}

		return true;
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

			if (false == l_entity.m_data.m_isVisible) {
				continue;
			}

			auto* lv_entityTexture = m_gpuResourceManager.RetrieveGpuTexture(l_entity.m_data.m_textureHandle);

			SDL_FRect lv_dstRect;
			lv_dstRect.x = l_entity.m_data.m_pos.x;
			lv_dstRect.y = l_entity.m_data.m_pos.y;
			lv_dstRect.w = (float)lv_entityTexture->w;
			lv_dstRect.h = (float)lv_entityTexture->h;

			if (false == SDL_RenderTexture(m_renderer, lv_entityTexture, nullptr, &lv_dstRect)) {
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