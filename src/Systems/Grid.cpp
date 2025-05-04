





#include "Systems/Grid.hpp"
#include "Engine.hpp"
#include <cmath>
#include "GeometryPrimitives/Circle.hpp"
#include "GeometryPrimitives/Rectangle.hpp"
#include "Entities/Entity.hpp"
#include "Systems/Collision.hpp"
#include <glm.hpp>
#include "Systems/CollisionReactionContext.hpp"
#include "Components/CollisionComponent.hpp"

#include "Systems/LogSystem.hpp"


namespace Asteroid
{
	

	Grid::Grid()
	{
		
		
	}


	void Grid::Init(const glm::ivec2& l_fullSizedWindowSize)
	{
		m_totalNumDivisionsX = (uint32_t)std::ceil((float)l_fullSizedWindowSize.x / (float)m_cellWidth);
		m_totalNumDivisionsY = (uint32_t)std::ceil((float)l_fullSizedWindowSize.y / (float)m_cellHeight);

		m_cells.resize(m_totalNumUint32PerCell * m_totalNumDivisionsX * m_totalNumDivisionsY);

		m_currentMaxNumCells = (uint32_t)(m_totalNumDivisionsX * m_totalNumDivisionsY);

		m_allIndicesInOneCell.resize(m_totalNumUint32PerCell * 32);
	}


	void Grid::Update(const glm::ivec2& l_currentWindowSize, const std::vector<Circle>& l_circleBounds, const std::vector<Entity>& l_entities)
	{
		memset(m_cells.data(), 0, sizeof(uint32_t) * m_cells.size());
		m_totalNumDivisionsX = (uint32_t)std::ceil((float)l_currentWindowSize.x / (float)m_cellWidth);
		m_totalNumDivisionsY = (uint32_t)std::ceil((float)l_currentWindowSize.y / (float)m_cellHeight);

		m_currentMaxNumCells = (uint32_t)(m_totalNumDivisionsY * m_totalNumDivisionsX);
	

		for (uint32_t j = 0; j < m_totalNumDivisionsY; ++j) {
			for (uint32_t i = 0; i < m_totalNumDivisionsX; ++i) {

				const Rectangle lv_currentCellRectangle
				{ .m_min{m_cellWidth * (i), m_cellHeight * (j)}
				, .m_max{m_cellWidth*(i+1), m_cellHeight*(j+1)}};

				for (uint32_t z = 0; z < (uint32_t)l_circleBounds.size(); ++z) {


					if (true == l_entities[z].IsActive()) {
						if (true == CircleRectangleIntersection(l_circleBounds[z], lv_currentCellRectangle)) {

							const uint32_t lv_quotient = z / 32U;
							const uint32_t lv_bitPlace = z % 32U;

							const uint32_t lv_indexOfFirstUint32Cell = (j * m_totalNumDivisionsX + i) * m_totalNumUint32PerCell;

							m_cells[lv_indexOfFirstUint32Cell + lv_quotient] |= (1 << lv_bitPlace);

						}
					}

				}

			}
		}

	}



	void Grid::DoCollisionDetection(const std::vector<Circle>& l_circleBounds, std::vector<Entity>& l_entities, Animation* l_animationSystem)
	{

		using namespace LogSystem;
	
		for (uint32_t j = 0; j < m_totalNumDivisionsY; ++j) {
			for (uint32_t i = 0; i < m_totalNumDivisionsX; ++i) {

				uint32_t lv_firstUint32IndexOfCell = (j * m_totalNumDivisionsX + i)*m_totalNumUint32PerCell;
				uint32_t lv_temp{};
				for (uint32_t d = 0; d < m_totalNumUint32PerCell; ++d) {
					for (uint32_t k = 0; k < 32; ++k) {

						if (0 != (m_cells[lv_firstUint32IndexOfCell + d] & (1 << k))) {
							m_allIndicesInOneCell[lv_temp] = (d * 32 + k);
							++lv_temp;
						}

					}
				}

				for (uint32_t k = 0; k < lv_temp; ++k) {

					const auto& lv_circle1 = l_circleBounds[m_allIndicesInOneCell[k]];
					CollisionComponent* lv_collisionComponentEntityK = (CollisionComponent*)l_entities[m_allIndicesInOneCell[k]].GetComponent(ComponentTypes::COLLISION);
					assert(nullptr != lv_collisionComponentEntityK);
					CollisionReactionContext lv_collisionReactContextEntityK{.m_animationSystem = l_animationSystem, .m_ownerEntity = &l_entities[m_allIndicesInOneCell[k]]};
					for (uint32_t d = k + 1; d < lv_temp; ++d) {

						const auto& lv_circle2 = l_circleBounds[m_allIndicesInOneCell[d]];
						const glm::vec2 lv_differenceVector = lv_circle1.m_center - lv_circle2.m_center;
						const float lv_sumOfRadiuses = lv_circle1.m_radius + lv_circle2.m_radius;

						if (glm::dot(lv_differenceVector, lv_differenceVector) <= (lv_sumOfRadiuses* lv_sumOfRadiuses)) {
							
							CollisionReactionContext lv_collisionReactContextEntityD{.m_animationSystem = l_animationSystem, .m_ownerEntity = &l_entities[m_allIndicesInOneCell[d]]};
							CollisionComponent* lv_collisionComponentEntityD = (CollisionComponent*)l_entities[m_allIndicesInOneCell[d]].GetComponent(ComponentTypes::COLLISION);

							lv_collisionComponentEntityK->CollisionReaction(l_entities[m_allIndicesInOneCell[d]], lv_collisionReactContextEntityK);
							lv_collisionComponentEntityD->CollisionReaction(l_entities[m_allIndicesInOneCell[k]], lv_collisionReactContextEntityD);

						}
					}
				}

			}
		}

	}


	bool Grid::CircleRectangleIntersection(const Circle& l_circle, const Rectangle& l_rectangle)
	{
		float lv_sqDistance{ 0.f };

		for (glm::vec<2, float, glm::packed_highp>::length_type i = 0; i < 2; ++i) {
			
			float lv_p = l_circle.m_center[i];

			if (lv_p < l_rectangle.m_min[i]) {
				lv_sqDistance += ((l_rectangle.m_min[i]-lv_p) * (l_rectangle.m_min[i] - lv_p));
			}
			if (lv_p > l_rectangle.m_max[i]) {
				lv_sqDistance += ((lv_p - l_rectangle.m_max[i]) * (lv_p - l_rectangle.m_max[i]));
			}
		}

		return lv_sqDistance <= (l_circle.m_radius * l_circle.m_radius);
	}


	uint32_t Grid::GetTotalNumNonEmptyCells() const
	{
		uint32_t lv_totalNumNonEmptyCells{};
		for (uint32_t i = 0; i < m_currentMaxNumCells * m_totalNumUint32PerCell; i += m_totalNumUint32PerCell) {
			if (0 != m_cells[i] || 0 != m_cells[i + 1] || 0 != m_cells[i + 2] || 0 != m_cells[i + 3]) {
				++lv_totalNumNonEmptyCells;
			}
		}

		return lv_totalNumNonEmptyCells;
	}


	uint32_t Grid::GetTotalNumCurrentCells() const
	{
		return m_currentMaxNumCells;
	}
}