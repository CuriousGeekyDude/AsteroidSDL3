


#include "Entities/Entity.hpp"
#include "Systems/LogSystem.hpp"
#include "Components/ComponentTypes.hpp"

namespace Asteroid
{
	Entity::Entity(const glm::vec2& l_initialPos, uint32_t l_id, const EntityType l_type, const bool l_isActive)
		:m_currentPos(l_initialPos), m_id(l_id)
		,m_type(l_type)
		,m_isActive(l_isActive)
	{

	}


	void Entity::AddComponent(const ComponentTypes l_componentType
		,std::unique_ptr<Component>&& l_component)
	{
		using namespace LogSystem;
		for (auto& l_component : m_components) {
			if (l_componentType == l_component.first) {
				LOG(Severity::INFO, Channel::INITIALIZATION
					, "Attempting to add duplicate component types to an entity: Add component request rejected.\n", nullptr);
				return;
			}
		}

		m_components.emplace_back(std::pair<ComponentTypes, std::unique_ptr<Component>>(l_componentType, std::move(l_component)));
	}



	EntityType Entity::GetType() const
	{
		return m_type;
	}

	const glm::vec2& Entity::GetCurrentPos() const
	{
		return m_currentPos;
	}


	bool Entity::Update(UpdateComponents& l_updateComponents)
	{
		for (auto& l_component : m_components) {
			if (false == l_component.second->Update(l_updateComponents)) {
				return false;
			}
		}

		return true;
	}





	void Entity::SetCurrentPos(const glm::vec2& l_newPos)
	{
		m_currentPos = l_newPos;
	}


	Component* Entity::GetComponent(const ComponentTypes l_componentType) const
	{

		for (auto& l_component : m_components) {
			if (l_componentType == l_component.first) {
				return l_component.second.get();
			}
		}

		return nullptr;
	}


	void Entity::SetActiveState(const bool l_activeState)
	{
		using namespace LogSystem;

		LOG(Severity::INFO, Channel::PROGRAM_LOGIC, "Active state is changed");
		m_isActive = l_activeState;
	}

	bool Entity::GetActiveState() const
	{
		return m_isActive;
	}

	uint32_t Entity::GetID() const
	{
		return m_id;
	}
}