#pragma once




namespace Asteroid
{

	class Engine;

	struct UpdateComponents final
	{
		float m_deltaTime{};
		Engine* m_engine{};
	};

}