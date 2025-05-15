#pragma once






#include <vector>
#include "Systems/TimeRewind/Frame.hpp"




namespace Asteroid
{

	class Entity;
	class InputSystem;
	struct DelayedSetStateCallback;
	class CallbacksTimer;

	class TimeRewind final
	{
	public:

		TimeRewind();


		void Update(const std::vector<Entity>& l_entities, const InputSystem& l_inputSystem ,const float l_time, const uint32_t l_totalNumBulletsHitAsteroid, const std::vector<DelayedSetStateCallback>& l_delayedCallbacks);


		void RewindTimeByOneFrame(std::vector<Entity>& l_entities, InputSystem& l_inputSystem,float& l_time, uint32_t& l_totalNumBulletsHitAsteroid, CallbacksTimer& l_callbackTimer);


		void Flush();


	private:
		constexpr static uint32_t m_totalNumPastFramesToRecord{1800U};
		std::vector<Frame> m_pastFrame{};
		uint32_t m_startIndex{};
		uint32_t m_endIndex{};
		bool m_firstTimeStartAndEndIndexAreSame{ true };
	};

}