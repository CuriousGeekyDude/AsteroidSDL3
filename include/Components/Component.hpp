#pragma once







namespace Asteroid
{
	class Entity;

	class Component
	{
	public:
		virtual ~Component() = default;

		virtual bool Update(float l_deltaTime) = 0;

		Component(Entity* l_ownerEntity);

	protected:
		Entity* m_ownerEntity;
	};
}