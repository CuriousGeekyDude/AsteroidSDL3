#pragma once




#include <glm.hpp>
#include <utility>
#include <vector>
#include <string>
#include <memory>
#include "Components/ComponentTypes.hpp"
#include "EntityType.hpp"
#include "Components/Component.hpp"



namespace Asteroid
{

	class Entity
	{
	public:

		Entity(const glm::vec2& l_initialPos, uint32_t l_id, const EntityType l_type);

		Entity(Entity&&) = default;
			
		void AddComponent(const ComponentTypes l_componentType, std::unique_ptr<Component>&& l_component);

		Component* GetComponent(const ComponentTypes l_componentType) const;

		bool Update(UpdateComponents& l_updateComponents);

		const glm::vec2& GetCurrentPos() const;

		void SetCurrentPos(const glm::vec2& l_newPos);


		EntityType GetType() const;

		virtual ~Entity() = default;

		uint32_t GetID() const;

	protected:

		glm::vec2 m_currentPos;
		uint32_t m_id;
		EntityType m_type;


		std::vector<std::pair<ComponentTypes ,std::unique_ptr<Component>>> m_components;
	};
}