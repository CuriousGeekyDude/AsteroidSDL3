#pragma once






#include "Components/StateComponent.hpp"
#include "Components/IndefiniteRepeatableAnimationComponent.hpp"


namespace Asteroid
{

	class CollisionComponent;
	class IndefiniteRepeatableAnimationComponent;

	class ActiveBasedStateComponent : public StateComponent
	{
	public:

		ActiveBasedStateComponent();

		bool Update(UpdateComponents& l_updateContext) override;


		void Init(EntityHandle l_ownerEntityHandle
			, CollisionComponent* l_collisionComponent
			, IndefiniteRepeatableAnimationComponent* l_repeatableAnimComponent
			, const uint32_t l_frameCountToActivate
			, const uint32_t l_frameCountToDeactivate);

		uint32_t GetframeCountToActivate() const;
		uint32_t GetframeCountToDeactivate() const;

		void SetDelayedActivationCallbackFlag(const bool l_newValue);

		void Reset();

	private:

		CollisionComponent* m_collisionComponent{};
		IndefiniteRepeatableAnimationComponent* m_repeatableAnimationComponent{};
		uint32_t m_frameCountToActivate;
		uint32_t m_frameCountToDeactivate;
		bool m_delayedActivateCallbackAlreadySet{ false };

	};

}