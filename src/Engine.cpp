

#include "Engine.hpp"
#include "Components/MovementComponents/UserInputBasedMovementComponent.hpp"
#include "Components/OnceRepeatableAnimationComponent.hpp"
#include "Components/IndefiniteRepeatableAnimationComponent.hpp"
#include "Components/RayMovementComponent.hpp"
#include "Components/StateComponents/ActiveBasedStateComponent.hpp"
#include "Components/CollisionComponents/PlayerCollisionComponent.hpp"
#include "Components/CollisionComponents/AsteroidCollisionComponent.hpp"
#include "Components/CollisionComponents/BulletCollisionComponent.hpp"
#include "Systems/Colors.hpp"
#include "Systems/RenderingData.hpp"
#include "Components/UpdateComponents.hpp"
#include "Systems/LogSystem.hpp"
#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_time.h>
#include <memory>

namespace Asteroid
{
	Engine::Engine(EngineInitData&& l_initialData)
		:m_initialData(std::move(l_initialData))
		,m_window(nullptr)
		,m_renderer(&m_gpuResourceManager)
		,m_inputSystem()
		,m_entityConnector(this)
		,m_entitySpawnerFromPools(this)
		,m_grid()
		,m_animationMetaData(std::move(m_initialData.m_animationMetaData))
	{
		
	}


	bool Engine::Init()
	{
		using namespace LogSystem;
		LOG(Severity::INFO, Channel::INITIALIZATION, "****Engine initialization has begun****\n");

		if (false == SDL_SetAppMetadata(m_initialData.m_appName.c_str()
			, m_initialData.m_appVersion.c_str(), nullptr)) {

			LOG(Severity::FAILURE, Channel::INITIALIZATION, "SDL Failed to create metadata for the app.");

		}



		Set_Verbosity(Severity::FAILURE);

		LOG(Severity::INFO, Channel::INITIALIZATION, "Metadata creation was successfull.");

		if (false == SDL_InitSubSystem(SDL_INIT_VIDEO)) {

			LOG(Severity::FAILURE, Channel::INITIALIZATION
				, "SDL failed to initialize at least one of the requested subsystems: %s", SDL_GetError());
			return false;
		}

		LOG(Severity::INFO, Channel::INITIALIZATION
			, "Initialization of all the requested subsystems was successfull.");

		
		m_window = SDL_CreateWindow
			(m_initialData.m_windowTitle.c_str(),0,0
			, SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED);
		
		if(nullptr == m_window){

			LOG(Severity::FAILURE, Channel::INITIALIZATION, "SDL failed to create window: %s", SDL_GetError());
			return false;

		}

		LOG(Severity::INFO, Channel::INITIALIZATION, "Window creation was successfull.");

		
		m_renderer.Init(m_window);
		m_renderer.SetClearColor(RenderSystem::Colors::BLACK);

		LOG(Severity::INFO, Channel::INITIALIZATION, "Creating textures on Gpu commencing....");

		for (auto& l_mapPairNameToPath : m_initialData.m_mappedTextureNamesToTheirPaths) {
			
			m_gpuResourceManager.CreateGpuTextureReturnHandle(m_renderer.GetSDLRenderer()
				, l_mapPairNameToPath.second, l_mapPairNameToPath.first);
		}

		m_backgroundStarsTextureHandle = m_gpuResourceManager.RetrieveGpuTextureHandle("BackgroundStarClusters");

		LOG(Severity::INFO, Channel::INITIALIZATION, "Creation of all textures on gpu was successful.");


		LOG(Severity::INFO, Channel::INITIALIZATION, "Initializing the entities....");

		Set_Verbosity(Severity::WARNING);

		InitEntitiesAndPools();

		glm::ivec2 lv_fullWindowSize{};
		GetCurrentWindowSize(lv_fullWindowSize);
		m_grid.Init(lv_fullWindowSize);

		LOG(Severity::INFO, Channel::INITIALIZATION, "Initializing entities was successful.");




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
		constexpr float lv_60fpsInMilliseconds{16.6666667f};
		UpdateComponents lv_updateComponent{};
		lv_updateComponent.m_engine = this;

		glm::ivec2 lv_currentWindowSize{};
		RenderSystem::RenderingData lv_backgroundStarsRenderData{};
		lv_backgroundStarsRenderData.m_angleOfRotation = 0.f;
		lv_backgroundStarsRenderData.m_entityPos = glm::vec2{ 0.f, 0.f };
		lv_backgroundStarsRenderData.m_entityTextureHandle = m_backgroundStarsTextureHandle;
		

		while (false == lv_quit) {

			m_trackLastFrameElapsedTime.m_currentTime = SDL_GetTicks();

			m_inputSystem.FlushNotAllowedRepetitionKeys();

			SDL_Event lv_event;
			static uint64_t lv_HideOrShow{};

			while (true == SDL_PollEvent(&lv_event)) {

				ImGui_ImplSDL3_ProcessEvent(&lv_event);
				m_inputSystem.ProcessInput(lv_event, m_window);

				if (true == m_inputSystem.IsKeyUp(InputSystem::Keys::KEY_F1)) {
					if (0 == lv_HideOrShow % 2) {
						show_demo_window = false;

					}
					else {
						show_demo_window = true;

					}
					++lv_HideOrShow;
				}


				if (SDL_EVENT_QUIT == lv_event.type) {
					lv_quit = true;
				}
			}


			assert(true == m_renderer.ClearWindow());
			GetCurrentWindowSize(lv_currentWindowSize);

			lv_backgroundStarsRenderData.m_heightToRender = lv_currentWindowSize.y;
			lv_backgroundStarsRenderData.m_widthToRender = lv_currentWindowSize.x;
			lv_backgroundStarsRenderData.m_centerOfRotation.x = (float)lv_currentWindowSize.x / 2.f;
			lv_backgroundStarsRenderData.m_centerOfRotation.y = (float)lv_currentWindowSize.y / 2.f;

			m_renderer.RenderEntity(lv_backgroundStarsRenderData);

			m_grid.Update(lv_currentWindowSize, m_circleBoundsEntities, m_entities);
			m_grid.DoCollisionDetection(m_circleBoundsEntities, m_entities, m_callbacksTimer);
			m_entitySpawnerFromPools.SpawnNewEntitiesIfConditionsMet();
			m_callbacksTimer.Update();
			lv_updateComponent.m_deltaTime = (float)m_trackLastFrameElapsedTime.m_lastFrameElapsedTime;
			for (auto& l_entity : m_entities) {
				if (true == l_entity.GetActiveState()) {
					assert(l_entity.Update(lv_updateComponent));
				}
			}
			m_entitySpawnerFromPools.UpdatePools();
			UpdateCircleBounds();

			


			ImGui_ImplSDLRenderer3_NewFrame();
			ImGui_ImplSDL3_NewFrame();
			ImGui::NewFrame();

			/*if (show_demo_window)
				ImGui::ShowDemoWindow(&show_demo_window);*/

			// 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
			{
				//static float f = 0.1f;

				auto& lv_player = m_entities[m_playerEntityHandle];

				ImGui::Begin("Player Info");                          // Create a window called "Hello, world!" and append into it.

				ImGui::Text("Angle of rotation: %f", -((UserInputBasedMovementComponent*)lv_player.GetComponent(ComponentTypes::MOVEMENT))->GetCurrentAngleOfRotation());
				//ImGui::SliderFloat("Speed", &f,0.1f, 5.f, "%.3f");
				
				ImGui::Text("Speed: (%f, %f)", m_entityConnector.RequestSpeedFromPlayer().x, m_entityConnector.RequestSpeedFromPlayer().y);
				ImGui::Text("Total number of non-empty cells: %u", m_grid.GetTotalNumNonEmptyCells());
				ImGui::Text("Total number of cells: %u", m_grid.GetTotalNumCurrentCells());

				/*auto* lv_movementComp = (PlayerMovementComponent*)lv_player.GetComponent(ComponentTypes::MOVEMENT);
				lv_movementComp->SetSpeed(f);*/
				

				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
				ImGui::End();
			}

			

			ImGui::Render();
			ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_renderer.GetSDLRenderer());

			assert(true == m_renderer.PresentToWindow());

			m_trackLastFrameElapsedTime.m_lastFrameElapsedTime = SDL_GetTicks() - m_trackLastFrameElapsedTime.m_currentTime;

			if (lv_60fpsInMilliseconds > m_trackLastFrameElapsedTime.m_lastFrameElapsedTime) {

				const uint64_t lv_delayTime = (uint64_t)(lv_60fpsInMilliseconds - m_trackLastFrameElapsedTime.m_lastFrameElapsedTime);
				m_trackLastFrameElapsedTime.m_lastFrameElapsedTime += lv_delayTime;
				SDL_Delay((uint32_t)lv_delayTime);

			}
		}

		LOG(LogSystem::Severity::INFO, LogSystem::Channel::GRAPHICS, "End of game loop.");

		return true;

	}


	Entity& Engine::GetEntityFromHandle(const EntityHandle l_entityHandle)
	{
		using namespace LogSystem;

		if ((uint32_t)m_entities.size() <= l_entityHandle.m_entityHandle) {
			LOG(Severity::FAILURE, Channel::MEMORY, "An attempt was made to access out of bound memory in vector of entities. The index used: %u\n", l_entityHandle.m_entityHandle);
			exit(EXIT_FAILURE);
		}
		else {
			return m_entities[l_entityHandle.m_entityHandle];
		}
	}
	const Entity& Engine::GetEntityFromHandle(const EntityHandle l_entityHandle) const
	{
		using namespace LogSystem;

		if ((uint32_t)m_entities.size() <= l_entityHandle.m_entityHandle) {
			LOG(Severity::FAILURE, Channel::MEMORY, "An attempt was made to access out of bound memory in vector of entities.\n");
			exit(EXIT_FAILURE);
		}
		else {
			return m_entities[l_entityHandle.m_entityHandle];
		}
	}

	Entity& Engine::GetEntityFromType(const EntityType l_type)
	{
		using namespace LogSystem;

		for (auto& l_entity : m_entities) {
			if (l_type == l_entity.GetType()) {
				return l_entity;
			}
		}

		LOG(Severity::FAILURE, Channel::PROGRAM_LOGIC, "No entity with the requested type exist yet.\n");
		exit(EXIT_FAILURE);
	}
	const Entity& Engine::GetEntityFromType(const EntityType l_type) const
	{
		using namespace LogSystem;

		for (const auto& l_entity : m_entities) {
			if (l_type == l_entity.GetType()) {
				return l_entity;
			}
		}

		LOG(Severity::FAILURE, Channel::PROGRAM_LOGIC, "No entity with the requested type exist yet.\n");
		exit(EXIT_FAILURE);
	}


	RenderSystem::Renderer* Engine::GetRenderer()
	{
		return &m_renderer;
	}


	const InputSystem& Engine::GetInputSystem() const
	{
		return m_inputSystem;
	}


	const std::vector<Entity>& Engine::GetEntities() const
	{
		return m_entities;
	}

	void Engine::InitEntitiesAndPools()
	{
		glm::ivec2 lv_windowRes{};
		GetCurrentWindowSize(lv_windowRes);

		m_circleBoundsEntities.reserve(150U);
		m_entities.reserve(150U);

		//Main player initialization
		{
			const auto* lv_spaceshipAnimMeta = GetAnimationMeta(AnimationType::MAIN_SPACESHIP);

			assert(nullptr != lv_spaceshipAnimMeta);


			auto lv_movementComponent = std::make_unique<UserInputBasedMovementComponent>();
			auto lv_collisionComponent = std::make_unique<PlayerCollisionComponent>();
			auto lv_entityAnimationComp = std::make_unique<IndefiniteRepeatableAnimationComponent>();
			auto lv_activeComponent = std::make_unique<ActiveBasedStateComponent>();

			lv_movementComponent->Init(0);
			lv_collisionComponent->Init(0, 0, 0, true, lv_entityAnimationComp.get());
			lv_entityAnimationComp->Init(0, lv_spaceshipAnimMeta, lv_movementComponent.get()
										,lv_activeComponent.get(), 0, 0, true);
			lv_activeComponent->Init(0, lv_collisionComponent.get(), lv_entityAnimationComp.get(),
				1, 1);
			auto& lv_player = m_entities.emplace_back(std::move(Entity(glm::vec2{ (float)lv_windowRes.x/2.f, (float)lv_windowRes.y/2.f }, 0, EntityType::PLAYER, true)));

			lv_player.AddComponent(ComponentTypes::MOVEMENT, std::move(lv_movementComponent));
			lv_player.AddComponent(ComponentTypes::ACTIVE_BASED_STATE, std::move(lv_activeComponent));
			lv_player.AddComponent(ComponentTypes::INDEFINITE_ENTITY_ANIMATION, std::move(lv_entityAnimationComp));
			lv_player.AddComponent(ComponentTypes::COLLISION, std::move(lv_collisionComponent));
			
			m_playerEntityHandle = 0U;
			
			m_circleBoundsEntities.push_back(Circle{ .m_center{lv_player.GetCurrentPos()}, .m_radius{lv_spaceshipAnimMeta->m_widthToRenderTextures/2.f} });
		}

		//Bullet entities and pool initialization
		{
			constexpr uint32_t lv_totalNumBullets{64U};
			const auto* lv_bulletAnimMetaData = GetAnimationMeta(AnimationType::LASER_BEAM);
			assert(nullptr != lv_bulletAnimMetaData);
			m_entitySpawnerFromPools.InitPool(Asteroid::EntityType::BULLET, (uint32_t)m_entities.size() ,lv_totalNumBullets);
			
			for (uint32_t i = 0U; i < lv_totalNumBullets; ++i) {

				const uint32_t lv_bulletIdx = 1U + i;

				auto lv_collisionComponent = std::make_unique<BulletCollisionComponent>();
				auto lv_movementComponent = std::make_unique<RayMovementComponent>();
				auto lv_activeComponent = std::make_unique<ActiveBasedStateComponent>();
				auto lv_entityMainAnimation = std::make_unique<IndefiniteRepeatableAnimationComponent>();

				lv_collisionComponent->Init(lv_bulletIdx,0, 0, true
											, lv_entityMainAnimation.get(), lv_activeComponent.get());
				lv_movementComponent->Init(lv_bulletIdx);
				lv_activeComponent->Init(lv_bulletIdx, lv_collisionComponent.get(), lv_entityMainAnimation.get(), 0, 0);
				lv_entityMainAnimation->Init(lv_bulletIdx, lv_bulletAnimMetaData, lv_movementComponent.get(), lv_activeComponent.get(), 0, 0, true);

				auto& lv_bullet = m_entities.emplace_back(std::move(Entity(glm::vec2{ 0.f, 0.f }, lv_bulletIdx, EntityType::BULLET, false)));
			

				lv_bullet.AddComponent(ComponentTypes::COLLISION, std::move(lv_collisionComponent));
				lv_bullet.AddComponent(ComponentTypes::ACTIVE_BASED_STATE, std::move(lv_activeComponent));
				lv_bullet.AddComponent(ComponentTypes::MOVEMENT, std::move(lv_movementComponent));
				lv_bullet.AddComponent(ComponentTypes::INDEFINITE_ENTITY_ANIMATION, std::move(lv_entityMainAnimation));
				

				
				m_circleBoundsEntities.push_back(Circle{ .m_center{lv_bullet.GetCurrentPos()}, .m_radius{lv_bulletAnimMetaData->m_widthToRenderTextures/2.f} });
				

			}

		}

		//Asteroid Entities and pool initialization
		{
			constexpr uint32_t lv_totalNumAsteroids{ 128U };
			const auto* lv_asteroidAnimMeta = GetAnimationMeta(AnimationType::ASTEROID);
			const auto* lv_explosionAsteroidAnimMeta = GetAnimationMeta(AnimationType::EXPLOSION_FIRE_ASTEROID);
			const auto* lv_warpAsteroidAnimMeta = GetAnimationMeta(AnimationType::WARP_ASTEROID);
			assert(nullptr != lv_asteroidAnimMeta);
			assert(nullptr != lv_warpAsteroidAnimMeta);
			const uint32_t lv_entitiesLastIndex = (uint32_t)m_entities.size();
			m_entitySpawnerFromPools.InitPool(Asteroid::EntityType::ASTEROID, lv_entitiesLastIndex, lv_totalNumAsteroids);

			for (uint32_t i = 0U; i < lv_totalNumAsteroids; ++i) {

				const uint32_t lv_asteroidIdx = lv_entitiesLastIndex + i;

				auto lv_collisionComponent = std::make_unique<AsteroidCollisionComponent>();
				auto lv_activeComponent = std::make_unique<ActiveBasedStateComponent>();
				auto lv_movementComponent = std::make_unique<RayMovementComponent>();
				auto lv_entityMainAnimation = std::make_unique<IndefiniteRepeatableAnimationComponent>();
				auto lv_fireExplosionAnimationComponent = std::make_unique<OnceRepeatableAnimationComponent>();
				auto lv_warpAsteroidAnimComponent = std::make_unique<OnceRepeatableAnimationComponent>();

				lv_collisionComponent->Init(lv_asteroidIdx, lv_warpAsteroidAnimMeta->m_totalNumFrames + 20U, lv_explosionAsteroidAnimMeta->m_totalNumFrames / 3
					, true, lv_entityMainAnimation.get(), lv_fireExplosionAnimationComponent.get()
					, lv_activeComponent.get());
				lv_activeComponent->Init(lv_asteroidIdx, lv_collisionComponent.get(), lv_entityMainAnimation.get()
										, 1, lv_explosionAsteroidAnimMeta->m_totalNumFrames);
				lv_movementComponent->Init(lv_asteroidIdx);
				lv_entityMainAnimation->Init(lv_asteroidIdx, lv_asteroidAnimMeta, lv_movementComponent.get()
											, lv_activeComponent.get(), lv_warpAsteroidAnimMeta->m_totalNumFrames - 20U, 0, true);
				lv_fireExplosionAnimationComponent->Init(lv_asteroidIdx, lv_explosionAsteroidAnimMeta , lv_movementComponent.get());
				lv_warpAsteroidAnimComponent->Init(lv_asteroidIdx, lv_warpAsteroidAnimMeta, lv_movementComponent.get(), false);

				auto& lv_asteroid = m_entities.emplace_back(std::move(Entity(glm::vec2{ 0.f, 0.f }, lv_asteroidIdx,  EntityType::ASTEROID, false)));

				lv_asteroid.AddComponent(ComponentTypes::COLLISION, std::move(lv_collisionComponent));
				lv_asteroid.AddComponent(ComponentTypes::ACTIVE_BASED_STATE, std::move(lv_activeComponent));
				lv_asteroid.AddComponent(ComponentTypes::MOVEMENT, std::move(lv_movementComponent));
				lv_asteroid.AddComponent(ComponentTypes::INDEFINITE_ENTITY_ANIMATION, std::move(lv_entityMainAnimation));
				lv_asteroid.AddComponent(ComponentTypes::EXPLOSION_FIRE_ASTEROID_ANIMATION, std::move(lv_fireExplosionAnimationComponent));
				lv_asteroid.AddComponent(ComponentTypes::WARP_ASTEROID_ANIMATION, std::move(lv_warpAsteroidAnimComponent));
				
				m_circleBoundsEntities.push_back(Circle{ .m_center{lv_asteroid.GetCurrentPos()}, .m_radius{lv_asteroidAnimMeta->m_widthToRenderTextures/2.f} });


			}
		}
	}

	void Engine::UpdateCircleBounds()
	{
		for (size_t i = 0; i < m_entities.size(); ++i) {
			if (true == m_entities[i].GetActiveState()) {
				m_circleBoundsEntities[i].m_center = m_entities[i].GetCurrentPos();
			}
		}
	}

	void Engine::GetCurrentWindowSize(glm::ivec2& l_windowRes) const
	{
		using namespace LogSystem;

		bool lv_result = SDL_GetWindowSize(m_window, &l_windowRes.x, &l_windowRes.y);

		if (false == lv_result) {
			LOG(Severity::FAILURE, Channel::GRAPHICS, "Failed to get current window size: %s", SDL_GetError());
			exit(EXIT_FAILURE);
		}

	}


	CallbacksTimer& Engine::GetCallbacksTimer()
	{
		return m_callbacksTimer;
	}


	const AnimationMetaData* Engine::GetAnimationMeta(const AnimationType l_type) const
	{
		for (const auto& l_metaData : m_animationMetaData) {
			if (l_type == l_metaData.m_type) {
				return &l_metaData;
			}
		}

		return nullptr;
	}

	const std::vector<Circle>& Engine::GetCircleBounds() const
	{
		return m_circleBoundsEntities;
	}


	const Grid& Engine::GetGrid() const
	{
		return m_grid;
	}


	Engine::~Engine()
	{

		ImGui_ImplSDLRenderer3_Shutdown();
		ImGui_ImplSDL3_Shutdown();
		ImGui::DestroyContext();

		SDL_DestroyWindow(m_window);
	}
}