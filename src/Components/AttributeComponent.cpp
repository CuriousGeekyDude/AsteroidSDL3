




#include "Components/AttributeComponent.hpp"



namespace Asteroid
{


	AttributeComponent::AttributeComponent()
	{

	}

	void AttributeComponent::Init(EntityHandle l_ownerEntityHandle, uint32_t l_hp)
	{
		Component::Init(l_ownerEntityHandle);

		m_initialHp = l_hp;
		m_hp = l_hp;
	}


	uint32_t AttributeComponent::GetHp() const
	{
		return m_hp;
	}

	void AttributeComponent::SetHP(const uint32_t l_hp)
	{
		m_hp = l_hp;
	}
}