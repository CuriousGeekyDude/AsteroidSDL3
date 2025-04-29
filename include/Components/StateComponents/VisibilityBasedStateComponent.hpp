#pragma once





#include "Components/StateComponent.hpp"



namespace Asteroid
{
	class GraphicsComponent;

	class VisibilityBasedStateComponent : public StateComponent
	{
	public:

		VisibilityBasedStateComponent(EntityHandle l_ownerEntityHandle
			, const GraphicsComponent* l_graphicsComponent);

		bool Update(UpdateComponents& l_updateContext) override;


	private:
		const GraphicsComponent* m_graphicsComponent{};
	};

}