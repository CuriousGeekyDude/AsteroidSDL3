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

		uint32_t GetHp() const;

		void SetHP(const uint32_t l_hp);

	protected:

		uint32_t m_hp{};
		uint32_t m_initialHp{};

	};

}