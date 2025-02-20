#pragma once




#include <glm.hpp>
#include "Components/Component.hpp"

namespace Asteroid
{
	class MovementComponent : public Component
	{
	public:
		
		MovementComponent();

		virtual ~MovementComponent() = default;


		bool Update(float l_lastFrameElapsedTime) override;

		void UpdateDeltaTransform(const glm::mat3& l_deltaTransform);

		const glm::mat3& GetTransform() const;

	protected:
		glm::mat3 m_transform{};
		glm::mat3 m_deltaTransform{};
	};
}