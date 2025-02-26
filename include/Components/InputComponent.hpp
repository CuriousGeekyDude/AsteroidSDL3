#pragma once



#include "Components/Component.hpp"


namespace Asteroid
{
	class Entity;

	class InputComponent : public Component
	{

	public:

		InputComponent(Entity* l_ownerEntity);

		virtual ~InputComponent() = default;
		
	};

}