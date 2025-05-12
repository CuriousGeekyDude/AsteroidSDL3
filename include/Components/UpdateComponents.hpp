#pragma once




namespace Asteroid
{

	class Engine;

	struct UpdateComponents final
	{
		float m_deltaTime{};
		Engine* m_engine{};
		uint32_t m_totalNumAsteroidsHitByBullets{};
	};

}