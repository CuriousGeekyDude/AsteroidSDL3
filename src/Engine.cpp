

#include "Engine.hpp"
#include "Components/PlayerComponents/PlayerInputComponent.hpp"
#include "Components/PlayerComponents/PlayerGraphicsComponent.hpp"
#include "Components/MovementComponent.hpp"
#include "Entities/PlayerEntity/PlayerEntity.hpp"
#include "Systems/Colors.hpp"
#include <SDL3/SDL.h>

namespace Asteroid
{
	Engine::Engine(EngineInitData&& l_initialData)
		:m_initialData(std::move(l_initialData))
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

		if (false == SDL_InitSubSystem(SDL_INIT_VIDEO)) {
			SDL_Log("SDL failed to initialize at least one of the requested subsystems: %s", SDL_GetError());
			return false;
		}

		SDL_Log("Initialization of all the requested subsystems was successfull.\n");



		
		m_window = SDL_CreateWindow
			(m_initialData.m_windowTitle.c_str()
			, (int)m_initialData.m_width
			, (int)m_initialData.m_height
			, SDL_WINDOW_RESIZABLE);
		
		if(nullptr == m_window){
			
			SDL_Log("SDL failed to create window: %s", SDL_GetError());
			return false;

		}

		SDL_Log("Window creation was successfull.\n");

		
		m_renderer.Init(m_window);
		m_renderer.SetClearColor(RenderSystem::Colors::BLACK);

		SDL_Log("Creating textures on Gpu commencing....\n");
		for (auto& l_mapPairNameToPath : m_initialData.m_mappedTextureNamesToTheirPaths) {
			
			m_gpuResourceManager.CreateGpuTextureReturnHandle(m_renderer.GetSDLRenderer()
				, l_mapPairNameToPath.second, l_mapPairNameToPath.first);


		}
		SDL_Log("Creation of all textures on gpu was successful.\n");


		SDL_Log("Initializing the entities....\n");

		InitEntities();

		SDL_Log("Initializing entities was successful.\n");


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

			assert(true == m_renderer.ClearWindow());
			for (auto& l_entity : m_entities) {
				assert(l_entity->Update((float)m_trackLastFrameElapsedTime.m_lastFrameElapsedTime));
			}
			assert(true == m_renderer.PresentToWindow());
			

			m_trackLastFrameElapsedTime.m_lastFrameElapsedTime = SDL_GetTicks() - m_trackLastFrameElapsedTime.m_currentTime;
		}

		return true;

	}



	void Engine::InitEntities()
	{
		auto* lv_spaceShipGpuTexture = m_gpuResourceManager.RetrieveGpuTexture("Spaceship");

		assert(nullptr != lv_spaceShipGpuTexture);

		auto lv_player = std::make_unique<PlayerEntity>(glm::vec2{ 0.f, 0.f }, 0);

		lv_player->AddComponent("PlayerMovement", std::make_unique<MovementComponent>());
		lv_player->AddComponent("PlayerInput", std::make_unique<PlayerInputComponent>((MovementComponent*)lv_player->GetComponent("PlayerMovement")));
		lv_player->AddComponent("PlayerGraphics", 
			std::make_unique<PlayerGraphicsComponent>
			(lv_player->GetInitialPos(), lv_spaceShipGpuTexture, (MovementComponent*)lv_player->GetComponent("PlayerMovement"), &m_renderer, lv_player.get()));

		m_entities.emplace_back(std::move(lv_player));

	}

	Engine::~Engine()
	{
		SDL_DestroyWindow(m_window);
	}
}