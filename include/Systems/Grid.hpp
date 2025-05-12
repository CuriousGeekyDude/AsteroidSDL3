#pragma once


#include <vector>
#include <glm.hpp>
#include "GeometryPrimitives/Circle.hpp"
#include "Entities/Entity.hpp"


namespace Asteroid
{

	class Engine;
	struct Rectangle;
	class Entity;
	class CallbacksTimer;

	class Grid final
	{
	public:

		Grid();


		void Init(const glm::ivec2& l_fullSizedWindowSize);

		void Update(const glm::ivec2& l_currentWindowSize, const std::vector<Circle>& l_circleBounds, const std::vector<Entity>& l_entities);

		void DoCollisionDetection(const std::vector<Circle>& l_circleBounds, std::vector<Entity>& l_entities, CallbacksTimer& l_timer);


		uint32_t GetTotalNumNonEmptyCells() const;
		uint32_t GetTotalNumCurrentCells() const;
		const std::vector<glm::vec2>& GetCurrentCenterPosCells() const;
	private:
		bool CircleRectangleIntersection(const Circle& l_circle, const Rectangle& l_rectangle);

	private:

		std::vector<uint32_t> m_cells{};
		std::vector<uint32_t> m_allIndicesInOneCell;
		std::vector<glm::vec2> m_centerPosOfCells;

		uint32_t m_currentMaxNumCells{};
		uint32_t m_totalNumDivisionsX{};
		uint32_t m_totalNumDivisionsY{};

		static constexpr uint32_t m_cellWidth{128U};
		static constexpr uint32_t m_cellHeight{ 128U };

		//This indicates that each cell can have at most 4x32 objects in it at any time
		static constexpr uint32_t m_totalNumUint32PerCell{4U};
	};

}