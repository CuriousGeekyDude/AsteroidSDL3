#pragma once




#include "Components/Component.hpp"

#include <glm.hpp>

namespace Asteroid
{

	namespace RenderSystem
	{
		class Renderer;
	}


	struct AnimationMetaData;
	class MovementComponent;
	class ActiveBasedStateComponent;
	
	class IndefiniteRepeatableAnimationComponent : public Component
	{
	public:

		IndefiniteRepeatableAnimationComponent();

		virtual bool Update(UpdateComponents& l_updateContext) override;


		void Init(const EntityHandle l_entityHandle
			, const AnimationMetaData* l_animationMetaData
			, const MovementComponent* l_movementComponent
			, ActiveBasedStateComponent* l_activeStateComponent
			, const uint32_t l_frameCountToActivateVisibility
			, const uint32_t l_frameCountToDeactivateVisibility
			, const bool l_visibleState = false);


		void SetVisibleState(const bool l_visibleState);

		bool GetVisibility() const;

		bool IsInWindowBounds() const;

		void Reset();

		uint32_t GetCurrentOffset() const;
		void SetCurrentOffset(const uint32_t l_newOffset);
		void SetWindowsBound(const bool l_windowsBound);


		uint32_t GetFrameCountToActivateVisbility() const;
		uint32_t GetFrameCountToDeactivateVisbility() const;

	private:

		const AnimationMetaData* m_animationMetaData;
		const MovementComponent* m_movementComponent;
		ActiveBasedStateComponent* m_activeStateComponent;

		uint32_t m_currentOffset{};
		bool m_isInWindowBound{true};
		bool m_isVisible;

		uint32_t m_frameCountToActivateVisibility;
		uint32_t m_frameCountToDeactivateVisibility;

	};

}