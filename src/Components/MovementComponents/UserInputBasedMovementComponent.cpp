



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
		auto& lv_ownerEntity = l_updateContext.m_engine->GetEntityFromHandle(m_ownerEntityHandle);

		const auto& lv_inputSystem = l_updateContext.m_engine->GetInputSystem();

		if (true == lv_inputSystem.IsMouseHidden()) {

			const auto& lv_mouseRelPos = lv_inputSystem.GetMousePosRelativeToWindow();
			auto& lv_currentPos = lv_ownerEntity.GetCurrentPos();

			glm::vec2 lv_newPos = lv_currentPos;

			if (true == lv_inputSystem.IsMouseButtonPressed(InputSystem::Mouse::LEFT)) {
				m_damper = (1 - std::expf(-m_damper));
				lv_newPos += m_damper * (lv_mouseRelPos - lv_currentPos);
			}
			else {
				m_damper = (1 - std::expf(-l_updateContext.m_deltaTime * 0.0015f));
			}
			
			lv_ownerEntity.SetCurrentPos(lv_newPos);

			glm::vec2 lv_directionVector{lv_mouseRelPos.x - lv_newPos.x, -lv_mouseRelPos.y + lv_newPos.y};
			
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
		

		}
		else {
			m_thetaDegrees = 0.f;
		}
		
		
		

		return true;
	}
}