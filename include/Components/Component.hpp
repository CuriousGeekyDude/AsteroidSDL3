#pragma once







namespace Asteroid
{
	class Component
	{
	public:
		virtual ~Component() = default;

		virtual bool Update(float l_lastFrameElapsedTime) = 0;
	};
}