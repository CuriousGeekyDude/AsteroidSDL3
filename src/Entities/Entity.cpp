


#include "Entities/Entity.hpp"
#include "Components/Component.hpp"
#include <SDL3/SDL_log.h>


namespace Asteroid
{
	Entity::Entity(const glm::vec2& l_initialPos, uint32_t l_id)
		:m_initialPos(l_initialPos), m_id(l_id)
	{

	}


	void Entity::AddComponent(const ComponentTypes l_componentType
		,std::unique_ptr<Component>&& l_component)
	{
		for (auto& l_component : m_components) {
			if (l_componentType == l_component.first) {
				SDL_Log("Attempting to add duplicate component types to an entity: Add component request rejected.\n");
				return;
			}
		}

		m_components.emplace_back(std::pair<ComponentTypes, std::unique_ptr<Component>>(l_componentType, std::move(l_component)));
	}


	const glm::vec2& Entity::GetInitialPos() const
	{
		return m_initialPos;
	}


	bool Entity::Update(const float l_lastFrameElapsedTime)
	{
		for (auto& l_component : m_components) {
			if (false == l_component.second->Update(l_lastFrameElapsedTime)) {
				return false;
			}
		}

		return true;
	}


	Component* Entity::GetComponent(const ComponentTypes l_componentType)
	{

		for (auto& l_component : m_components) {
			if (l_componentType == l_component.first) {
				return l_component.second.get();
			}
		}

		return nullptr;
	}
}