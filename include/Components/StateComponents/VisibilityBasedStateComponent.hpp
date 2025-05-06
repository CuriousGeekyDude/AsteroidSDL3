#pragma once





#include "Components/StateComponent.hpp"



namespace Asteroid
{
	class GraphicsComponent;
	class ActiveBasedStateComponent;
	struct AnimationMetaData;

	class VisibilityBasedStateComponent : public StateComponent
	{
	public:

		VisibilityBasedStateComponent(EntityHandle l_ownerEntityHandle
			, const AnimationMetaData* l_animationMetaData);

		bool Update(UpdateComponents& l_updateContext) override;

		bool GetVisibility() const;

		void SetVisibility(const bool l_visibility);

	private:
		const AnimationMetaData* m_animationMetaData{};
		bool m_isVisible{ true };
	};

}