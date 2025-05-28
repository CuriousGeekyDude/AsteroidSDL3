#pragma once






#include "Components/AttributeComponent.hpp"


namespace Asteroid
{

	class PlayerAttributeComponent : public AttributeComponent
	{
	public:

		PlayerAttributeComponent();


		void Init(EntityHandle l_ownerEntityHandle, uint32_t l_hp);

		bool Update(UpdateComponents& l_updateContext) override;

		void DecrementHPByOne();

		void ResetHealth();

	private:

	};

}