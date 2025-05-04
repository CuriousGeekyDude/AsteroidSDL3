


#include "Entities/Entity.hpp"
#include "Systems/LogSystem.hpp"
#include "Components/ComponentTypes.hpp"
#include "Components/StateComponents/DelayDeactiveBasedStateComponent.hpp"
#include "Components/CollisionComponent.hpp"

namespace Asteroid
{
	Entity::Entity(const glm::vec2& l_initialPos, uint32_t l_id, const bool l_isActive, const EntityType l_type)
		:m_currentPos(l_initialPos), m_id(l_id), m_isActive(l_isActive)
		,m_type(l_type)
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



	bool Entity::IsActive() const
	{
		return m_isActive;
	}


	void Entity::SetInactive()
	{
		using namespace LogSystem;

		auto* lv_delayComponent = (DelayDeactiveBasedStateComponent*)GetComponent(ComponentTypes::DELAY_BASED_STATE);
		auto* lv_collisionComponent = (CollisionComponent*)GetComponent(ComponentTypes::COLLISION);


		if (nullptr != lv_collisionComponent) {
			LOG(Severity::INFO, Channel::PHYSICS, "Entity with index %u has reset its collision flag.", m_id);
			lv_collisionComponent->ResetCollision();
		}


		if (nullptr == lv_delayComponent) {
			m_isActive = false;
		}
		else {

			if (true == lv_delayComponent->HasStartedFrameCount()) {
				LOG(Severity::FAILURE, Channel::PROGRAM_LOGIC, "Entity with id %u is being deactivated when the delayed deactivation component is still active.", m_id);
				exit(EXIT_FAILURE);
			}
			else {
				m_isActive = false;
			}

		}
	}

	void Entity::SetActive()
	{
		m_isActive = true;
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

	uint32_t Entity::GetID() const
	{
		return m_id;
	}
}