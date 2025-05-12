




#include "Components/AttributeComponent.hpp"



namespace Asteroid
{


	AttributeComponent::AttributeComponent()
	{

	}

	void AttributeComponent::Init(EntityHandle l_ownerEntityHandle, uint32_t l_hp)
	{
		Component::Init(l_ownerEntityHandle);


		m_hp = l_hp;
	}

}