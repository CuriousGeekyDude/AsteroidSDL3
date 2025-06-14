





#include "Systems/Grid.hpp"
#include "Engine.hpp"
#include <cmath>
#include "GeometryPrimitives/Circle.hpp"
#include "GeometryPrimitives/Rectangle.hpp"
#include "Entities/Entity.hpp"
#include <glm.hpp>
#include "Components/CollisionComponent.hpp"
#include "Components/StateComponents/ActiveBasedStateComponent.hpp"
#include "Systems/EventSystem/EventManager.hpp"
#include "Systems/LogSystem.hpp"
#include "Systems/MemoryAlloc.hpp"
#include "Systems/EventSystem/EventCollision.hpp"

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

		m_centerPosOfCells.resize(m_currentMaxNumCells);

		m_allIndicesInOneCell.resize(m_totalNumUint32PerCell * 32);
	}


	void Grid::Update(const glm::ivec2& l_currentWindowSize, const std::vector<Circle>& l_circleBounds, const std::vector<Entity>& l_entities)
	{
		memset(m_cells.data(), 0, sizeof(uint32_t) * m_cells.size());
		memset(m_centerPosOfCells.data(), 0, sizeof(float)*m_centerPosOfCells.size());
		m_totalNumDivisionsX = (uint32_t)std::ceil((float)l_currentWindowSize.x / (float)m_cellWidth);
		m_totalNumDivisionsY = (uint32_t)std::ceil((float)l_currentWindowSize.y / (float)m_cellHeight);

		m_currentMaxNumCells = (uint32_t)(m_totalNumDivisionsY * m_totalNumDivisionsX);
		

		constexpr float lv_halfCellWidth{(float)m_cellWidth/2.f};
		constexpr float lv_halfCellHeight{ (float)m_cellHeight / 2.f };

		for (uint32_t j = 0U; j < m_totalNumDivisionsY; ++j) {
			for (uint32_t i = 0U; i < m_totalNumDivisionsX; ++i) {

				m_centerPosOfCells[j * m_totalNumDivisionsX + i] = glm::vec2{(float)i*m_cellWidth + lv_halfCellWidth, (float)j*m_cellHeight + lv_halfCellHeight};

			}
		}


		for (uint32_t j = 0; j < m_totalNumDivisionsY; ++j) {
			for (uint32_t i = 0; i < m_totalNumDivisionsX; ++i) {

				const Rectangle lv_currentCellRectangle
				{ .m_min{m_cellWidth * (i), m_cellHeight * (j)}
				, .m_max{m_cellWidth*(i+1), m_cellHeight*(j+1)}};

				for (uint32_t z = 0; z < (uint32_t)l_circleBounds.size(); ++z) {

					CollisionComponent* lv_collisionComp = (CollisionComponent*)l_entities[z].GetComponent(ComponentTypes::COLLISION);
					if (nullptr == lv_collisionComp) { continue; }
					if (true == l_entities[z].GetActiveState() && true == lv_collisionComp->GetCollisionState()) {
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



	void Grid::DoCollisionDetection(const std::vector<Circle>& l_circleBounds, std::vector<Entity>& l_entities, CallbacksTimer& l_timer, EventManager& l_eventManager, MemoryAlloc& l_memAlloc)
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
					for (uint32_t d = k + 1; d < lv_temp; ++d) {

						const auto& lv_circle2 = l_circleBounds[m_allIndicesInOneCell[d]];
						const glm::vec2 lv_differenceVector = lv_circle1.m_center - lv_circle2.m_center;
						const float lv_sumOfRadiuses = lv_circle1.m_radius + lv_circle2.m_radius;

						if (glm::dot(lv_differenceVector, lv_differenceVector) <= (lv_sumOfRadiuses* lv_sumOfRadiuses)) {
							
							CollisionComponent* lv_collisionComponentEntityD = (CollisionComponent*)l_entities[m_allIndicesInOneCell[d]].GetComponent(ComponentTypes::COLLISION);


							EventCollision* lv_collisionEvent = static_cast<EventCollision*>(l_memAlloc.Allocate(sizeof(EventCollision)));
							lv_collisionEvent = new(lv_collisionEvent) EventCollision(&l_entities[m_allIndicesInOneCell[d]], &l_entities[m_allIndicesInOneCell[k]], &l_timer);

							std::function<void()> lv_collisionDelegate{
								[lv_collisionComponentEntityK, lv_collisionComponentEntityD, lv_collisionEvent, &l_memAlloc]() -> void
								{
									lv_collisionComponentEntityD->CollisionReaction(lv_collisionEvent);
									lv_collisionComponentEntityK->CollisionReaction(lv_collisionEvent);

									l_memAlloc.Destruct<EventCollision>(lv_collisionEvent, sizeof(EventCollision));
								}
							};

							l_eventManager.AssociateNewDelegateToEventType(lv_collisionEvent->GetType(), std::move(lv_collisionDelegate));
							l_eventManager.AddNewEventToEventQueue(lv_collisionEvent);
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




	const std::vector<glm::vec2>& Grid::GetCurrentCenterPosCells() const
	{
		return m_centerPosOfCells;
	}


	uint32_t Grid::GetTotalNumCurrentCells() const
	{
		return m_currentMaxNumCells;
	}
}