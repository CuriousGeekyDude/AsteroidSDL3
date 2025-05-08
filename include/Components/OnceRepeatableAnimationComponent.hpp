#pragma once




#include "Components/Component.hpp"



namespace Asteroid
{

	struct AnimationMetaData;
	class MovementComponent;

	class OnceRepeatableAnimationComponent : public Component
	{

	public:

		OnceRepeatableAnimationComponent();

		bool Update(UpdateComponents& l_updateContext) override;

		void StartAnimation();


		void Init(const EntityHandle l_entityHandle
			, const AnimationMetaData* l_animationMetaData
			, const MovementComponent* l_movementComponent);

	private:

		const AnimationMetaData* m_animationMetaData;
		const MovementComponent* m_movementComponent;

		uint32_t m_currentOffset{};

		bool m_startAnimation{ false };
	};


}