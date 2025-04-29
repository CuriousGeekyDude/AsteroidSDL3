#pragma once


#include <vector>



namespace Asteroid
{

	class Engine;
	struct Circle;
	struct Rectangle;

	class Grid final
	{
	public:

		Grid();


		void Init(const Engine* l_engine);

		void Update(const Engine* l_engine);

		void DoCollisionDetection(Engine* l_engine);


		uint32_t GetTotalNumNonEmptyCells() const;
		uint32_t GetTotalNumCurrentCells() const;
	private:
		bool CircleRectangleIntersection(const Circle& l_circle, const Rectangle& l_rectangle);

	private:

		std::vector<uint32_t> m_cells{};
		std::vector<uint32_t> m_allIndicesInOneCell;
		uint32_t m_currentMaxNumCells{};
		static constexpr uint32_t m_cellWidth{128U};
		static constexpr uint32_t m_cellHeight{ 128U };

		//This indicates that each cell can have at most 4x32 objects in it at any time
		static constexpr uint32_t m_totalNumUint32PerCell{4U};
	};

}