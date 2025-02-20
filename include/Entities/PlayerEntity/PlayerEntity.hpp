#pragma once



#include "Entities/Entity.hpp"


namespace Asteroid
{

	class PlayerEntity : public Entity
	{
	public:

		PlayerEntity(const glm::vec2& l_initialPos, const uint32_t l_id);

		bool Update(const float l_lastFrameElapsedTime) override;


	private:

	};


}