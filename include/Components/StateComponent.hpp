#pragma once




#include "Components/Component.hpp"



namespace Asteroid
{

	class StateComponent : public Component
	{
	public:

		StateComponent();

		void Init(EntityHandle l_ownerEntityHandle);

	};

}