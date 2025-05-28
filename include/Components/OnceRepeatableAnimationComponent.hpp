#pragma once




#include "Components/Component.hpp"
#include <glm.hpp>



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
			, const MovementComponent* l_movementComponent
			, const bool l_followEntity = true);

		const AnimationMetaData* GetAnimationMetaData() const;

		uint32_t GetCurrentOffset() const;
		bool AnimationHasStarted() const;
		const glm::vec2& GetInitialAnimationPos() const;

		void SetCurrentOffset(const uint32_t l_newOffset);
		void SetInitialAnimationPos(const glm::vec2& l_initialEntityPos);
		void SetAnimationStartState(const bool l_startAnimation);

		void Reset();

	private:

		const AnimationMetaData* m_animationMetaData;
		const MovementComponent* m_movementComponent;

		uint32_t m_currentOffset{};

		bool m_startAnimation{ false };

		bool m_followEntity{ true };

		glm::vec2 m_initialEntityPos{};
	};


}