



#include "Components/Component.hpp"




namespace Asteroid
{
	Component::Component(EntityHandle l_ownerEntityHandle, Engine* l_engine)
		:m_ownerEntityHandle(l_ownerEntityHandle), m_engine(l_engine)
	{

	}
}