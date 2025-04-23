#pragma once



#include "Entities/EntityHandle.hpp"


namespace Asteroid
{
	struct EntityHandle;
	class EntityConnector;
	class Engine;

	class Component
	{
	public:
		virtual ~Component() = default;

		virtual bool Update(float l_deltaTime) = 0;

		Component(EntityHandle l_ownerEntityHandle, Engine* l_engine);

	protected:

		Engine* m_engine;
		EntityHandle m_ownerEntityHandle;
	};
}