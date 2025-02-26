



#include "Components/PlayerComponents/PlayerMovementComponent.hpp"
#include "Components/PlayerComponents/PlayerInputComponent.hpp"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Entities/Entity.hpp"

namespace Asteroid
{
	PlayerMovementComponent::PlayerMovementComponent(const PlayerInputComponent* l_playerInputComponent
	, Entity* l_ownerEntity)
		:MovementComponent(l_ownerEntity)
		, m_playerInputComponent(l_playerInputComponent)
		
	{

	}


	bool PlayerMovementComponent::Update(float l_deltaTime)
	{
		glm::mat3 lv_deltaTransform = glm::identity<glm::mat3>();
		glm::vec3 lv_deltaPos{ 0.f };
		constexpr float lv_speedDamper{ 0.1f };

		const auto& lv_keyStates = m_playerInputComponent->GetKeyStates();

		if (true == lv_keyStates[(int)PlayerInputComponent::Keys::KEY_W]) {
			lv_deltaPos.y = -1.f * (lv_speedDamper * l_deltaTime);
		}
		if (true == lv_keyStates[(int)PlayerInputComponent::Keys::KEY_S]) {
			lv_deltaPos.y = (lv_speedDamper * l_deltaTime);
		}
		if (true == lv_keyStates[(int)PlayerInputComponent::Keys::KEY_D]) {
			lv_deltaPos.x = (lv_speedDamper * l_deltaTime);
		}
		if (true == lv_keyStates[(int)PlayerInputComponent::Keys::KEY_A]) {
			lv_deltaPos.x = -1.f * (lv_speedDamper * l_deltaTime);
		}

		if (0 != lv_deltaPos.x || 0 != lv_deltaPos.y) {
			lv_deltaTransform[2][0] = lv_deltaPos.x;
			lv_deltaTransform[2][1] = lv_deltaPos.y;

			m_transform = lv_deltaTransform * m_transform;
			auto& lv_currentPos = m_ownerEntity->GetCurrentPos();
			auto lv_newPos3 = lv_deltaTransform * glm::vec3{ lv_currentPos, 1.f };

			m_ownerEntity->SetCurrentPos(glm::vec2{ lv_newPos3.x, lv_newPos3.y });
		}

		return true;
	}
}