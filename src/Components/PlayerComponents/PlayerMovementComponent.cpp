



#include "Components/PlayerComponents/PlayerMovementComponent.hpp"
#include "Components/PlayerComponents/PlayerInputComponent.hpp"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

namespace Asteroid
{
	PlayerMovementComponent::PlayerMovementComponent(const PlayerInputComponent* l_playerInputComponent)
		:m_playerInputComponent(l_playerInputComponent)
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

		lv_deltaTransform[2][0] = lv_deltaPos.x;
		lv_deltaTransform[2][1] = lv_deltaPos.y;

		m_transform = lv_deltaTransform*m_transform;

		return true;
	}
}