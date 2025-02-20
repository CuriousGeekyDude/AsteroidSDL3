


#include "Entities/Entity.hpp"
#include "Components/Component.hpp"



namespace Asteroid
{
	Entity::Entity(const glm::vec2& l_initialPos, uint32_t l_id)
		:m_initialPos(l_initialPos), m_id(l_id)
	{

	}


	void Entity::AddComponent(std::string&& l_componentName
		,std::unique_ptr<Component>&& l_component)
	{
		m_components.emplace_back(std::pair<std::string, std::unique_ptr<Component>>(std::move(l_componentName), std::move(l_component)));
	}


	const glm::vec2& Entity::GetInitialPos() const
	{
		return m_initialPos;
	}

	Component* Entity::GetComponent(const std::string& l_componentName)
	{

		for (auto& l_component : m_components) {
			if (l_componentName == l_component.first) {
				return l_component.second.get();
			}
		}

		return nullptr;
	}
}