



#include "Components/MovementComponents/UserInputBasedMovementComponent.hpp"
#include "Engine.hpp"
#include "Components/UpdateComponents.hpp"
#include <algorithm>

namespace Asteroid
{
	UserInputBasedMovementComponent::UserInputBasedMovementComponent()
		
	{

	}



	void UserInputBasedMovementComponent::Init(EntityHandle l_ownerEntityHandle)
	{
		Component::Init(l_ownerEntityHandle);
	}

	bool UserInputBasedMovementComponent::Update(UpdateComponents& l_updateContext)
	{
		glm::mat3 lv_deltaTransform = glm::identity<glm::mat3>();
		bool lv_keyIsPressed = false;
		float lv_d = (1 - std::expf(-l_updateContext.m_deltaTime * 0.16f));
		float lv_damper{ 0.065f };
		
		float lv_tempSpeed{ lv_damper * lv_d * l_updateContext.m_deltaTime };


		const auto& lv_inputSystem = l_updateContext.m_engine->GetInputSystem();

		if (true == lv_inputSystem.IsRepetitionAllowedKeyPressed(InputSystem::Keys::KEY_W)) {
			m_speed += glm::vec2(0.f, -lv_tempSpeed);
			lv_keyIsPressed = true;
		}
		if (true == lv_inputSystem.IsRepetitionAllowedKeyPressed(InputSystem::Keys::KEY_S)) {
			m_speed += glm::vec2(0.f, lv_tempSpeed);
			lv_keyIsPressed = true;


		}
		if (true == lv_inputSystem.IsRepetitionAllowedKeyPressed(InputSystem::Keys::KEY_D)) {
			m_speed += glm::vec2(lv_tempSpeed, 0.f);
			lv_keyIsPressed = true;
		}
		if (true == lv_inputSystem.IsRepetitionAllowedKeyPressed(InputSystem::Keys::KEY_A)) {
			
			m_speed += glm::vec2(-lv_tempSpeed, 0.f);
			lv_keyIsPressed = true;


		}
		if (false == lv_keyIsPressed) {
			lv_tempSpeed = std::clamp(lv_tempSpeed, 0.001f, 0.99f);
			m_speed = m_speed * lv_tempSpeed;
 		}
		const float lv_speedLimit{3.5f};
		m_speed = glm::vec2(std::clamp(m_speed.x, -lv_speedLimit, lv_speedLimit), std::clamp(m_speed.y, -lv_speedLimit, lv_speedLimit));
		lv_deltaTransform[2][0] = m_speed.x;
		lv_deltaTransform[2][1] = m_speed.y;

		auto& lv_ownerEntity = l_updateContext.m_engine->GetEntityFromHandle(m_ownerEntityHandle);

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
					m_thetaDegrees = glm::pi<float>() + glm::acos(lv_normalizedDirectionVector.x);
				}
				else {
					m_thetaDegrees = glm::acos(lv_normalizedDirectionVector.x);
				}
				m_thetaDegrees = m_thetaDegrees - (glm::pi<float>()/2.f);
				m_thetaDegrees *= -1.f;
				m_thetaDegrees = glm::degrees<float>(m_thetaDegrees);
			}
			else {
				m_thetaDegrees = 0.f;
			}
			
		}
		else {
			m_thetaDegrees = 0.f;
		}
		
		
		

		return true;
	}
}