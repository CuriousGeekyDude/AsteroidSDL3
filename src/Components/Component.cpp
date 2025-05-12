



#include "Components/Component.hpp"




namespace Asteroid
{
	Component::Component()
	{

	}

	void Component::Init(EntityHandle l_ownerEntityHandle)
	{
		m_ownerEntityHandle = l_ownerEntityHandle;
	}
}