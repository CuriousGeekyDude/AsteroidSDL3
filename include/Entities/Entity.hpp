#pragma once




#include <glm.hpp>
#include <utility>
#include <vector>
#include <string>
#include <memory>



namespace Asteroid
{

	class Component;

	class Entity
	{
	public:

		Entity(const glm::vec2& l_initialPos, uint32_t l_id);
			
		void AddComponent(std::string&& l_componentName, std::unique_ptr<Component>&& l_component);

		Component* GetComponent(const std::string& l_componentName);

		virtual bool Update(const float l_lastFrameElapsedTime) = 0;

		const glm::vec2& GetInitialPos() const;

		virtual ~Entity() = default;

	protected:

		glm::vec2 m_initialPos;
		uint32_t m_id;

		std::vector<std::pair<std::string ,std::unique_ptr<Component>>> m_components;
	};
}