#pragma once






#include "Components/StateComponent.hpp"



namespace Asteroid
{

	class DelayDeactiveBasedStateComponent : public StateComponent
	{
	public:

		DelayDeactiveBasedStateComponent(EntityHandle l_ownerEntityHandle, const uint32_t l_maxNumFrames);



		bool Update(UpdateComponents& l_updateContext) override;

		bool HasStartedFrameCount() const;

		void StartCount();

	private:

		bool m_startFrameCount{ false };
		uint32_t m_frameCount{};
		uint32_t m_maxNumFrames{};


	};

}