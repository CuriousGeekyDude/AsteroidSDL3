#pragma once




#include <glm.hpp>
#include <utility>
#include <vector>
#include <string>
#include <memory>
#include "../Components/ComponentTypes.hpp"



namespace Asteroid
{

	class Component;

	class Entity
	{
	public:

		Entity(const glm::vec2& l_initialPos, uint32_t l_id, const bool l_isActive);

		Entity(Entity&&) = default;
			
		void AddComponent(const ComponentTypes l_componentType, std::unique_ptr<Component>&& l_component);

		Component* GetComponent(const ComponentTypes l_componentType);

		bool Update(const float l_deltaTime);

		const glm::vec2& GetCurrentPos() const;

		void SetCurrentPos(const glm::vec2& l_newPos);

		bool IsActive() const;

		virtual ~Entity() = default;

	protected:

		glm::vec2 m_currentPos;
		uint32_t m_id;
		bool m_isActive;

		std::vector<std::pair<ComponentTypes ,std::unique_ptr<Component>>> m_components;
	};
}