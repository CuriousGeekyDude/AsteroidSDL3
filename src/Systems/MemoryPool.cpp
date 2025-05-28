





#include "Systems/MemoryPool.hpp"
#include "Systems/LogSystem.hpp"
#include <cmath>
#include <stdexcept>
#include <cassert>


namespace Asteroid
{


	MemoryPool::MemoryPool(const size_t l_minBytesToAllocate, const size_t l_blockSizes)
		: m_blockSizeInBytes(l_blockSizes)
	{
		using namespace LogSystem;


		assert(0 == l_blockSizes % 16);

		m_totalBytesAllocatedForPool =  static_cast<size_t>(std::powf(2.f,std::ceilf(std::log2f((float)l_minBytesToAllocate))));
		
		m_totalNumFreeList = static_cast<uint32_t>(m_totalBytesAllocatedForPool / m_blockSizeInBytes);

		if (0U == m_totalNumFreeList) {
			throw std::runtime_error("Pool failed to initialize");
		}

		
		m_array = new unsigned char[m_totalBytesAllocatedForPool];


		for (size_t i = 0, j = 0; i < m_totalBytesAllocatedForPool; i += m_blockSizeInBytes, ++j) {

			//Violates strict aliasing rules which compiler assumes us to respect when doing optimization.
			uint32_t* lv_tempArray = reinterpret_cast<uint32_t*>(&m_array[i]);
			lv_tempArray[0] = m_gaurdDebugValue;
			lv_tempArray[1] = (uint32_t)(j+1);

		}

		auto lv_sizeOfAllBlocksExceptLast = m_totalBytesAllocatedForPool - m_blockSizeInBytes;
		uint32_t* lv_lastBlock = reinterpret_cast<uint32_t*>(&m_array[lv_sizeOfAllBlocksExceptLast]);
		lv_lastBlock[1] = UINT32_MAX;

	}


	
	void* MemoryPool::Allocate()
	{
		using namespace LogSystem;

		if (0U == m_totalNumFreeList) {
			return nullptr;
		}

		//Violates strict aliasing rules which compiler assumes us to respect when doing optimization.
		uint32_t* lv_blockToReturn = reinterpret_cast<uint32_t*>(&m_array[m_blockSizeInBytes * m_headHandleOfFreeList]);
		uint32_t lv_nextBlockHandle = lv_blockToReturn[1];

		m_headHandleOfFreeList = lv_nextBlockHandle;
		--m_totalNumFreeList;

		return static_cast<void*>(lv_blockToReturn);

	}



	bool MemoryPool::Deallocate(void* l_block)
	{
		using namespace LogSystem;

		auto lv_integerCastBlockPtr = reinterpret_cast<uintptr_t>(l_block);

		if (nullptr == l_block) {
			LOG(Severity::WARNING, Channel::MEMORY, "Tried to free nullptr from the pool");
			return false;
		}

		if (reinterpret_cast<uintptr_t>(m_array) <= lv_integerCastBlockPtr && lv_integerCastBlockPtr <= reinterpret_cast<uintptr_t>(&m_array[m_totalBytesAllocatedForPool-1])) {
			
			unsigned char* lv_currentBlock = static_cast<unsigned char*>(l_block);

			size_t lv_totalNumBytesInBetween = lv_currentBlock - m_array;

			uint32_t lv_blockToBeFreedHandle = static_cast<uint32_t>(lv_totalNumBytesInBetween / m_blockSizeInBytes);

			//Violates strict aliasing rules which compiler assumes us to respect when doing optimization.
			uint32_t* lv_currentBlockUint32 = reinterpret_cast<uint32_t*>(l_block);
			lv_currentBlockUint32[0] = m_gaurdDebugValue;
			lv_currentBlockUint32[1] = m_headHandleOfFreeList;
			m_headHandleOfFreeList = lv_blockToBeFreedHandle;
			++m_totalNumFreeList;
			return true;

		}
		else {

			throw std::runtime_error("Memory that was requested to be deallocated from the pool was not in the range of the pool");

		}

	}

	MemoryPool::~MemoryPool()
	{
		delete[] m_array;
	}


}