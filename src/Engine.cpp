

#include "Engine.hpp"
#include "Components/PlayerComponents/PlayerGraphicsComponent.hpp"
#include "Components/PlayerComponents/PlayerMovementComponent.hpp"
#include "Entities/Entity.hpp"
#include "Systems/Colors.hpp"

#define LOGGING
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
		using namespace LogSystem;
		LOG(Severity::INFO, Channel::INITIALIZATION, "****Engine initialization has begun****\n", nullptr);
		//LogSystem::LogCommandLine("****Engine initialization has begun****\n");

		if (false == SDL_SetAppMetadata(m_initialData.m_appName.c_str()
			, m_initialData.m_appVersion.c_str(), nullptr)) {

			LOG(Severity::FAILURE, Channel::INITIALIZATION, "SDL Failed to create metadata for the app.", nullptr);


			/*LogSystem::LogCommandLine("SDL Failed to create metadata for the app."
				, "ERROR",  "INITIALIZATION", __LINE__, __FILE__);*/

		}


		LOG(Severity::INFO, Channel::INITIALIZATION, "Metadata creation was successfull.", nullptr);

		/*LogSystem::LogCommandLine(""
			, "INFO", "INITIALIZATION", __LINE__, __FILE__);*/


		if (false == SDL_InitSubSystem(SDL_INIT_VIDEO)) {

			LOG(Severity::FAILURE, Channel::INITIALIZATION
				, "SDL failed to initialize at least one of the requested subsystems: ", SDL_GetError());
			return false;
		}

		LOG(Severity::INFO, Channel::INITIALIZATION
			, "Initialization of all the requested subsystems was successfull.", nullptr);

		
		m_window = SDL_CreateWindow
			(m_initialData.m_windowTitle.c_str()
			, (int)m_initialData.m_width
			, (int)m_initialData.m_height
			, SDL_WINDOW_RESIZABLE);
		
		if(nullptr == m_window){

			LOG(Severity::FAILURE, Channel::INITIALIZATION, "SDL failed to create window: ", SDL_GetError());
			return false;

		}

		LOG(Severity::INFO, Channel::INITIALIZATION, "Window creation was successfull.", nullptr);

		
		m_renderer.Init(m_window);
		m_renderer.SetClearColor(RenderSystem::Colors::BLACK);

		LOG(Severity::INFO, Channel::INITIALIZATION, "Creating textures on Gpu commencing....", nullptr);

		for (auto& l_mapPairNameToPath : m_initialData.m_mappedTextureNamesToTheirPaths) {
			
			m_gpuResourceManager.CreateGpuTextureReturnHandle(m_renderer.GetSDLRenderer()
				, l_mapPairNameToPath.second, l_mapPairNameToPath.first);
		}

		LOG(Severity::INFO, Channel::INITIALIZATION, "Creation of all textures on gpu was successful.", nullptr);

		LOG(Severity::INFO, Channel::INITIALIZATION, "Initializing the entities....", nullptr);

		InitEntities();

		LOG(Severity::INFO, Channel::INITIALIZATION, "Initializing entities was successful.", nullptr);

		

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