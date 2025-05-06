#pragma once




#include "Components/GraphicsComponent.hpp"



namespace Asteroid
{

	class AnimationComponent : public GraphicsComponent
	{

	public:

		AnimationComponent(const EntityHandle l_entityHandle
			, const AnimationMetaData* l_animationMetaData);


		bool Update(UpdateComponents& l_updateContext) override;


		void StartAnimation();

	private:

		bool m_startAnimation{ false };

	};


}