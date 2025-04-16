



#include "Components/PlayerComponents/PlayerMovementComponent.hpp"
#include "Systems/InputSystem.hpp"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <algorithm>
#include "Entities/Entity.hpp"

namespace Asteroid
{
	PlayerMovementComponent::PlayerMovementComponent(
	Entity* l_ownerEntity, const InputSystem* l_inputSystem)
		:MovementComponent(l_ownerEntity, l_inputSystem)
		
	{

	}


	bool PlayerMovementComponent::Update(float l_deltaTime)
	{
		glm::mat3 lv_deltaTransform = glm::identity<glm::mat3>();
		bool lv_keyIsPressed = false;
		float lv_d = l_deltaTime / (1.f + l_deltaTime);

		const auto& lv_keyStates = m_inputSystem->GetKeyStates();

		if (true == lv_keyStates[(int)InputSystem::Keys::KEY_W]) {
			m_speed += glm::vec2(0.f, -0.01f * lv_d);
			lv_keyIsPressed = true;
		}
		if (true == lv_keyStates[(int)InputSystem::Keys::KEY_S]) {
			m_speed += glm::vec2(0.f, 0.01f * lv_d);
			lv_keyIsPressed = true;


		}
		if (true == lv_keyStates[(int)InputSystem::Keys::KEY_D]) {

			m_speed += glm::vec2(0.01f * lv_d, 0.f);
			lv_keyIsPressed = true;


		}
		if (true == lv_keyStates[(int)InputSystem::Keys::KEY_A]) {
			
			m_speed += glm::vec2(-0.01f * lv_d, 0.f);
			lv_keyIsPressed = true;


		}
		if (false == lv_keyIsPressed) {
			m_speed = m_speed * (1-std::expf(-l_deltaTime*30.f));
 		}
		m_speed = glm::vec2(std::clamp(m_speed.x, -0.3f, 0.3f), std::clamp(m_speed.y, -0.3f, 0.3f));
		lv_deltaTransform[2][0] = m_speed.x;
		lv_deltaTransform[2][1] = m_speed.y;

		m_transform = lv_deltaTransform * m_transform;
		auto& lv_currentPos = m_ownerEntity->GetCurrentPos();
		auto lv_newPos3 = lv_deltaTransform * glm::vec3{ lv_currentPos, 1.f };
		m_ownerEntity->SetCurrentPos(glm::vec2{ lv_newPos3.x, lv_newPos3.y });



		if (true == m_inputSystem->IsMouseHidden()) {

			const auto& lv_mouseRelPos = m_inputSystem->GetMousePosRelativeToWindow();
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