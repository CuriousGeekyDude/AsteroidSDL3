





#include "Components/AttributeComponents/PlayerAttributeComponent.hpp"



namespace Asteroid
{

	PlayerAttributeComponent::PlayerAttributeComponent()
	{

	}


	void PlayerAttributeComponent::Init(EntityHandle l_ownerEntityHandle, uint32_t l_hp)
	{
		AttributeComponent::Init(l_ownerEntityHandle, l_hp);
	}

	bool PlayerAttributeComponent::Update(UpdateComponents& l_updateContext)
	{
		return true;
	}


	void PlayerAttributeComponent::DecrementHPByOne()
	{
		if (m_hp > 0) {
			--m_hp;
		}
	}

	void PlayerAttributeComponent::ResetHealth()
	{
		m_hp = m_initialHp;
	}
}