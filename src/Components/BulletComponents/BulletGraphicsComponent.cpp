



#include "Components/BulletComponents/BulletGraphicsComponent.hpp"
#include "Entities/Entity.hpp"
#include "Components/RayMovementComponent.hpp"
#include "Systems/RenderingData.hpp"
#include "Systems/Renderer.hpp"
#include "Engine.hpp"
#include "Components/UpdateComponents.hpp"

#include "Systems/LogSystem.hpp"

namespace Asteroid
{
	BulletGraphicsComponent::BulletGraphicsComponent(uint32_t l_textureHandle, EntityHandle l_entityHandle
		, const RayMovementComponent* l_bulletMovementComponent)
		:GraphicsComponent(l_textureHandle,l_entityHandle)
		,m_bulletMovementComponent(l_bulletMovementComponent)
	{

	}


	bool BulletGraphicsComponent::Update(UpdateComponents& l_updateContext)
	{
		glm::ivec2 lv_windowRes{};
		auto& lv_ownerEntity = l_updateContext.m_engine->GetEntityFromHandle(m_ownerEntityHandle);

		l_updateContext.m_engine->GetCurrentWindowSize(lv_windowRes);

		const auto& lv_currentPos = lv_ownerEntity.GetCurrentPos();


		constexpr int lv_widthToRender{50};
		constexpr int lv_heightToRender{ 50 };

		constexpr float lv_halfWidthToRender{((float)lv_widthToRender)/2.f};
		constexpr float lv_halfHeightToRender{ ((float)lv_heightToRender) / 2.f };


		if (lv_currentPos.x <= -lv_halfWidthToRender || lv_currentPos.x >= ((float)lv_windowRes.x + lv_halfWidthToRender)
			|| lv_currentPos.y >= ((float)lv_windowRes.y + lv_halfHeightToRender) || lv_currentPos.y <= -lv_halfHeightToRender) {

			lv_ownerEntity.SetInactive();
			return true;

		}
		else {

			auto* lv_renderer = l_updateContext.m_engine->GetRenderer();

			const float lv_theta = m_bulletMovementComponent->GetCurrentAngleOfRotation();
			RenderSystem::RenderingData lv_renderData{};
			lv_renderData.m_widthToRender = lv_widthToRender;
			lv_renderData.m_heightToRender = lv_heightToRender;
			lv_renderData.m_centerOfRotation = glm::vec2{ (float)lv_renderData.m_widthToRender / 2.f, (float)lv_renderData.m_heightToRender / 2.f };
			lv_renderData.m_entityPos = lv_currentPos - lv_renderData.m_centerOfRotation;
			lv_renderData.m_entityTextureHandle = m_textureHandle;
			lv_renderData.m_angleOfRotation = lv_theta;

			if (false == lv_renderer->RenderEntity(lv_renderData)) {
				return false;
			}

			return true;

		}
		


	}
}