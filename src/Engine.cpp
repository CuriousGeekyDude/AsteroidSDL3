

#include "Engine.hpp"
#include "Components/PlayerComponents/PlayerGraphicsComponent.hpp"
#include "Components/PlayerComponents/PlayerMovementComponent.hpp"
#include "Entities/Entity.hpp"
#include "Systems/Colors.hpp"

#define LOGGING
#include "Systems/LogSystem.hpp"
#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>
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
			(m_initialData.m_windowTitle.c_str(),0,0
			, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
		
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

		Set_Verbosity(Severity::WARNING);

		InitEntities();

		LOG(Severity::INFO, Channel::INITIALIZATION, "Initializing entities was successful.", nullptr);

		

		


		return true;
	}


	bool Engine::GameLoop()
	{

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// Setup Platform/Renderer backends
		ImGui_ImplSDL3_InitForSDLRenderer(m_window, m_renderer.GetSDLRenderer());
		ImGui_ImplSDLRenderer3_Init(m_renderer.GetSDLRenderer());


		bool lv_quit = false;
		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.f, 0.f, 0.f, 1.00f);
		while (false == lv_quit) {

			m_trackLastFrameElapsedTime.m_currentTime = SDL_GetTicks();

			SDL_Event lv_event;

			while (true == SDL_PollEvent(&lv_event)) {

				ImGui_ImplSDL3_ProcessEvent(&lv_event);

				if (SDL_EVENT_QUIT == lv_event.type) {
					lv_quit = true;
				}
			}

			m_inputSystem.ProcessInput();

			assert(true == m_renderer.ClearWindow());
			for (auto& l_entity : m_entities) {
				assert(l_entity.Update((float)m_trackLastFrameElapsedTime.m_lastFrameElapsedTime));
			}
			


			ImGui_ImplSDLRenderer3_NewFrame();
			ImGui_ImplSDL3_NewFrame();
			ImGui::NewFrame();

			// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
			if (show_demo_window)
				ImGui::ShowDemoWindow(&show_demo_window);

			// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
			{
				static float f = 0.0f;
				static int counter = 0;

				ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

				ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
				ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
				ImGui::Checkbox("Another Window", &show_another_window);

				ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
				ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

				if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
					counter++;
				ImGui::SameLine();
				ImGui::Text("counter = %d", counter);

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
				ImGui::End();
			}

			// 3. Show another simple window.
			if (show_another_window)
			{
				ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
				ImGui::Text("Hello from another window!");
				if (ImGui::Button("Close Me"))
					show_another_window = false;
				ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_renderer.GetSDLRenderer());

			assert(true == m_renderer.PresentToWindow());

			m_trackLastFrameElapsedTime.m_lastFrameElapsedTime = SDL_GetTicks() - m_trackLastFrameElapsedTime.m_currentTime;
		}
		Set_Verbosity(LogSystem::Severity::INFO);
		LOG(LogSystem::Severity::INFO, LogSystem::Channel::GRAPHICS, "End of game loop.", nullptr);

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

		ImGui_ImplSDLRenderer3_Shutdown();
		ImGui_ImplSDL3_Shutdown();
		ImGui::DestroyContext();

		SDL_DestroyWindow(m_window);
	}
}