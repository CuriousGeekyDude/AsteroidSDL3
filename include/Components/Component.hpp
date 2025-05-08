#pragma once



#include "Entities/EntityHandle.hpp"

namespace Asteroid
{
	struct UpdateComponents;

	class Component
	{
	public:
		virtual ~Component() = default;

		virtual bool Update(UpdateComponents& l_updateContext) = 0;

		Component();


		void Init(EntityHandle l_ownerEntityHandle);

	protected:
		EntityHandle m_ownerEntityHandle;
	};
}