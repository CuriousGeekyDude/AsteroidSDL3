



#include "Entities/PlayerEntity/PlayerEntity.hpp"
#include "Components/Component.hpp"


namespace Asteroid
{
	PlayerEntity::PlayerEntity(const glm::vec2& l_initialPos, const uint32_t l_id)
		:Entity(l_initialPos, l_id)
	{

	}

	bool PlayerEntity::Update(const float l_lastFrameElapsedTime)
	{
		for (auto& l_component : m_components) {
			if (false == l_component.second->Update(l_lastFrameElapsedTime)) {
				return false;
			}
		}

		return true;
	}
}