


#include "Entities/Entity.hpp"
#include "Components/Component.hpp"
#include "Systems/LogSystem.hpp"


namespace Asteroid
{
	Entity::Entity(const glm::vec2& l_initialPos, uint32_t l_id)
		:m_currentPos(l_initialPos), m_id(l_id)
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


	const glm::vec2& Entity::GetCurrentPos() const
	{
		return m_currentPos;
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


	void Entity::SetCurrentPos(const glm::vec2& l_newPos)
	{
		m_currentPos = l_newPos;
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