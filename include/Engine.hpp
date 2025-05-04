#pragma once



#include "EngineInitData.hpp"
#include "Time.hpp"
#include "Systems/GpuResouceManager.hpp"
#include "Systems/Renderer.hpp"
#include "Systems/InputSystem.hpp"
#include "Systems/EntityConnector.hpp"
#include "Entities/EntityType.hpp"
#include "Entities/EntityHandle.hpp"
#include "Entities/Entity.hpp"
#include "GeometryPrimitives/Circle.hpp"
#include "Entities/EntitySpawnerFromPools.hpp"
#include "Systems/Grid.hpp"
#include <vector>
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


		Entity& GetEntityFromHandle(const EntityHandle l_entityHandle);
		const Entity& GetEntityFromHandle(const EntityHandle l_entityHandle) const;

		//Iterates entities and returns the first one that has that type
		Entity& GetEntityFromType(const EntityType l_type);
		const Entity& GetEntityFromType(const EntityType l_type) const;


		const std::vector<Entity>& GetEntities() const;


		RenderSystem::Renderer* GetRenderer();

		const InputSystem& GetInputSystem() const;

		void GetCurrentWindowSize(glm::ivec2& l_windowRes) const;

		const std::vector<Circle>& GetCircleBounds() const;
		void UpdateCircleBounds();

		~Engine();

	public:

		EntityConnector m_entityConnector;


	private:

		void InitEntitiesAndPools();

	private:

		EngineInitData m_initialData;

		//Wanted to have pointer here but vector of entities might grow
		//and invalidate the ptr.
		uint32_t m_playerEntityHandle{};
		std::vector<Entity> m_entities{};
		std::vector<Circle> m_circleBoundsEntities{};
		Time m_trackLastFrameElapsedTime;

		RenderSystem::Renderer m_renderer;
		InputSystem m_inputSystem;
		EntitySpawnerFromPools m_entitySpawnerFromPools;
		Grid m_grid;

		GpuResourceManager m_gpuResourceManager;

		SDL_Window* m_window;
	};


}