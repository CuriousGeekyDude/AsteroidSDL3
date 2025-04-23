



#include "Components/PlayerComponents/PlayerMovementComponent.hpp"
#include "Systems/InputSystem.hpp"
#include "Engine.hpp"
#include "Entities/Entity.hpp"
#include <algorithm>

namespace Asteroid
{
	PlayerMovementComponent::PlayerMovementComponent(
	EntityHandle l_ownerEntityHandle, Engine* l_engine)
		:MovementComponent(l_ownerEntityHandle, l_engine)
		
	{

	}


	bool PlayerMovementComponent::Update(float l_deltaTime)
	{
		glm::mat3 lv_deltaTransform = glm::identity<glm::mat3>();
		bool lv_keyIsPressed = false;
		float lv_d = (1 - std::expf(-l_deltaTime * 0.16f));
		float lv_damper{ 0.064f };
		
		const auto& lv_inputSystem = m_engine->GetInputSystem();

		if (true == lv_inputSystem.IsKeyPressedNoRepetition(InputSystem::Keys::KEY_W)) {
			m_speed += glm::vec2(0.f, -lv_damper * lv_d * l_deltaTime);
			lv_keyIsPressed = true;
		}
		if (true == lv_inputSystem.IsKeyPressedNoRepetition(InputSystem::Keys::KEY_S)) {
			m_speed += glm::vec2(0.f, lv_damper * lv_d * l_deltaTime);
			lv_keyIsPressed = true;


		}
		if (true == lv_inputSystem.IsKeyPressedNoRepetition(InputSystem::Keys::KEY_D)) {
			m_speed += glm::vec2(lv_damper * lv_d * l_deltaTime, 0.f);
			lv_keyIsPressed = true;
		}
		if (true == lv_inputSystem.IsKeyPressedNoRepetition(InputSystem::Keys::KEY_A)) {
			
			m_speed += glm::vec2(-lv_damper * lv_d * l_deltaTime, 0.f);
			lv_keyIsPressed = true;


		}
		if (false == lv_keyIsPressed) {
			m_speed = m_speed * lv_d * l_deltaTime* lv_damper;
 		}
		const float lv_speedLimit{3.5f};
		m_speed = glm::vec2(std::clamp(m_speed.x, -lv_speedLimit, lv_speedLimit), std::clamp(m_speed.y, -lv_speedLimit, lv_speedLimit));
		lv_deltaTransform[2][0] = m_speed.x;
		lv_deltaTransform[2][1] = m_speed.y;

		auto& lv_ownerEntity = m_engine->GetEntityFromHandle(m_ownerEntityHandle);

		m_transform = lv_deltaTransform * m_transform;
		auto& lv_currentPos = lv_ownerEntity.GetCurrentPos();
		auto lv_newPos3 = lv_deltaTransform * glm::vec3{ lv_currentPos, 1.f };
		lv_ownerEntity.SetCurrentPos(glm::vec2{ lv_newPos3.x, lv_newPos3.y });



		if (true == lv_inputSystem.IsMouseHidden()) {

			const auto& lv_mouseRelPos = lv_inputSystem.GetMousePosRelativeToWindow();
			glm::vec2 lv_directionVector{lv_mouseRelPos.x - lv_newPos3.x, -lv_mouseRelPos.y + lv_newPos3.y};
			
			if (0 != glm::dot(lv_directionVector, lv_directionVector)) {

				glm::vec2 lv_normalizedDirectionVector = glm::normalize(lv_directionVector);

				if (lv_normalizedDirectionVector.y < 0) {
					lv_normalizedDirectionVector *= -1.f;
					m_theta = glm::pi<float>() + glm::acos(lv_normalizedDirectionVector.x);
				}
				else {
					m_theta = glm::acos(lv_normalizedDirectionVector.x);
				}
				m_theta = m_theta - (glm::pi<float>()/2.f);
				m_theta *= -1.f;
				m_theta = glm::degrees<float>(m_theta);
			}
			else {
				m_theta = 0.f;
			}
			
		}
		else {
			m_theta = 0.f;
		}
		
		
		

		return true;
	}
}