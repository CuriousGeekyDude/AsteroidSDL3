

#include "Engine.hpp"
#include "Components/PlayerComponents/PlayerGraphicsComponent.hpp"
#include "Components/PlayerComponents/PlayerMovementComponent.hpp"
#include "Entities/Entity.hpp"
#include "Systems/Colors.hpp"
#include "Systems/LogSystem.hpp"
#include <SDL3/SDL.h>
#include <memory>

namespace Asteroid
{
	Engine::Engine(EngineInitData&& l_initialData)
		:m_initialData(std::move(l_initialData))
		,m_window(nullptr)
		,m_renderer(&m_gpuResourceManager)
		,m_inputSystem()
	{
		
	}


	bool Engine::Init()
	{
		LogSystem::LogCommandLine("****Engine initialization has begun****\n");

		if (false == SDL_SetAppMetadata(m_initialData.m_appName.c_str()
			, m_initialData.m_appVersion.c_str(), nullptr)) {

			LogSystem::LogCommandLine("SDL Failed to create metadata for the app."
				, "ERROR",  "INITIALIZATION", __LINE__, __FILE__);

		}

		LogSystem::LogCommandLine("Metadata creation was successfull."
			, "INFO", "INITIALIZATION", __LINE__, __FILE__);


		if (false == SDL_InitSubSystem(SDL_INIT_VIDEO)) {
			LogSystem::LogCommandLine("SDL failed to initialize at least one of the requested subsystems: {4}."
				, "ERROR", "INITIALIZATION", __LINE__, __FILE__, SDL_GetError());
			return false;
		}



		LogSystem::LogCommandLine("Initialization of all the requested subsystems was successfull."
			, "INFO", "INITIALIZATION", __LINE__, __FILE__);

		
		m_window = SDL_CreateWindow
			(m_initialData.m_windowTitle.c_str()
			, (int)m_initialData.m_width
			, (int)m_initialData.m_height
			, SDL_WINDOW_RESIZABLE);
		
		if(nullptr == m_window){
			LogSystem::LogCommandLine("SDL failed to create window: {4}."
				, "ERROR", "INITIALIZATION", __LINE__, __FILE__, SDL_GetError());
			return false;

		}

		LogSystem::LogCommandLine("Window creation was successfull."
			, "INFO", "INITIALIZATION", __LINE__, __FILE__);

		
		m_renderer.Init(m_window);
		m_renderer.SetClearColor(RenderSystem::Colors::BLACK);



		LogSystem::LogCommandLine("Creating textures on Gpu commencing...."
			, "INFO", "INITIALIZATION", __LINE__, __FILE__);
		for (auto& l_mapPairNameToPath : m_initialData.m_mappedTextureNamesToTheirPaths) {
			
			m_gpuResourceManager.CreateGpuTextureReturnHandle(m_renderer.GetSDLRenderer()
				, l_mapPairNameToPath.second, l_mapPairNameToPath.first);


		}
		LogSystem::LogCommandLine("Creation of all textures on gpu was successful."
			, "INFO", "INITIALIZATION", __LINE__, __FILE__);

		LogSystem::LogCommandLine("Initializing the entities...."
			, "INFO", "INITIALIZATION", __LINE__, __FILE__);

		InitEntities();

		LogSystem::LogCommandLine("Initializing entities was successful."
			, "INFO", "INITIALIZATION", __LINE__, __FILE__);

		return true;
	}


	bool Engine::GameLoop()
	{

		bool lv_quit = false;
		while (false == lv_quit) {

			m_trackLastFrameElapsedTime.m_currentTime = SDL_GetTicks();

			SDL_Event lv_event;

			while (true == SDL_PollEvent(&lv_event)) {
				if (SDL_EVENT_QUIT == lv_event.type) {
					lv_quit = true;
				}
			}

			m_inputSystem.ProcessInput();

			assert(true == m_renderer.ClearWindow());
			for (auto& l_entity : m_entities) {
				assert(l_entity.Update((float)m_trackLastFrameElapsedTime.m_lastFrameElapsedTime));
			}
			assert(true == m_renderer.PresentToWindow());
			

			m_trackLastFrameElapsedTime.m_lastFrameElapsedTime = SDL_GetTicks() - m_trackLastFrameElapsedTime.m_currentTime;
		}

		return true;

	}



	void Engine::InitEntities()
	{
		uint32_t lv_spaceShipGpuTextureHandle = m_gpuResourceManager.RetrieveGpuTextureHandle("Spaceship");

		assert(UINT32_MAX != lv_spaceShipGpuTextureHandle);

		auto& lv_player = m_entities.emplace_back(std::move(Entity(glm::vec2{ 0.f, 0.f }, 0)));

		lv_player.AddComponent(ComponentTypes::MOVEMENT, std::make_unique<PlayerMovementComponent>( &lv_player, &m_inputSystem));
		lv_player.AddComponent(ComponentTypes::GRAPHICS, 
			std::make_unique<PlayerGraphicsComponent>(lv_spaceShipGpuTextureHandle, &m_renderer, &lv_player));


	}

	Engine::~Engine()
	{
		SDL_DestroyWindow(m_window);
	}
}