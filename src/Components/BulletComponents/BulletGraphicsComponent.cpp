



#include "Components/BulletComponents/BulletGraphicsComponent.hpp"
#include "Entities/Entity.hpp"
#include "Components/RayMovementComponent.hpp"
#include "Systems/RenderingData.hpp"
#include "Systems/Renderer.hpp"
#include "Engine.hpp"

#include "Systems/LogSystem.hpp"

namespace Asteroid
{
	BulletGraphicsComponent::BulletGraphicsComponent(uint32_t l_textureHandle
		, RenderSystem::Renderer* l_renderer, EntityHandle l_entityHandle
		, const glm::ivec2& l_windowResolution
		, const RayMovementComponent* l_bulletMovementComponent
		, Engine* l_engine)
		:GraphicsComponent(l_textureHandle, l_renderer, l_entityHandle, l_windowResolution, l_engine)
		,m_bulletMovementComponent(l_bulletMovementComponent)
	{

	}


	bool BulletGraphicsComponent::Update(float l_deltaTime)
	{
		using namespace LogSystem;
		
		LOG(Severity::INFO, Channel::MEMORY, "Bullet entity with index %u is being accessed", m_ownerEntityHandle);
		auto& lv_ownerEntity = m_engine->GetEntityFromHandle(m_ownerEntityHandle);

		m_engine->GetCurrentWindowSize(m_windowResolution);

		const auto& lv_currentPos = lv_ownerEntity.GetCurrentPos();


		constexpr int lv_widthToRender{50};
		constexpr int lv_heightToRender{ 50 };

		constexpr float lv_halfWidthToRender{((float)lv_widthToRender)/2.f};
		constexpr float lv_halfHeightToRender{ ((float)lv_heightToRender) / 2.f };


		if (lv_currentPos.x <= -lv_halfWidthToRender || lv_currentPos.x >= ((float)m_windowResolution.x + lv_halfWidthToRender)
			|| lv_currentPos.y >= ((float)m_windowResolution.y + lv_halfHeightToRender) || lv_currentPos.y <= -lv_halfHeightToRender) {

			lv_ownerEntity.SetInactive();
			return true;

		}
		else {

			const float lv_theta = m_bulletMovementComponent->GetCurrentAngleOfRotation();
			RenderSystem::RenderingData lv_renderData{};
			lv_renderData.m_widthToRender = lv_widthToRender;
			lv_renderData.m_heightToRender = lv_heightToRender;
			lv_renderData.m_centerOfRotation = glm::vec2{ (float)lv_renderData.m_widthToRender / 2.f, (float)lv_renderData.m_heightToRender / 2.f };
			lv_renderData.m_entityPos = lv_currentPos - lv_renderData.m_centerOfRotation;
			lv_renderData.m_entityTextureHandle = m_textureHandle;
			lv_renderData.m_angleOfRotation = lv_theta;

			if (false == m_renderer->RenderEntity(lv_renderData)) {
				return false;
			}

			return true;

		}
		


	}
}