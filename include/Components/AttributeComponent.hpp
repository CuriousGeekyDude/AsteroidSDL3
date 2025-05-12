#pragma once






#include "Components/Component.hpp"



namespace Asteroid
{


	class AttributeComponent : public Component
	{

	public:

		AttributeComponent();

		void Init(EntityHandle l_ownerEntityHandle, uint32_t l_hp);

		virtual ~AttributeComponent() = default;

	private:

		uint32_t m_hp{};

	};

}