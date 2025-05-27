





#include "Systems/MemoryPool.hpp"
#include <cmath>


namespace Asteroid
{


	MemoryPool::MemoryPool(const size_t l_minBytesToAllocate, const size_t l_blockSizes)
		: m_blockSizeInBytes(l_blockSizes)
	{
		using namespace LogSystem;

		//Total bytes will always be the smallest power of 2 bigger than the requested bytes
		m_totalBytesAllocatedForPool =  static_cast<size_t>(std::powf(2.f,std::ceilf(std::log2f((float)l_minBytesToAllocate))));
		
		m_totalNumFreeList = static_cast<uint32_t>(m_totalBytesAllocatedForPool / m_blockSizeInBytes);

		if (0U == m_totalNumFreeList) {
			return;
		}

		if (m_totalBytesAllocatedForPool < m_blockSizeInBytes) {
			LOG(Severity::WARNING, Channel::MEMORY, "Failed to initialize pool: size of a single block is bigger than the total size of the pool");
			return;
		}


		m_array = new char[m_totalBytesAllocatedForPool];

		if (nullptr == m_array) {
			LOG(Severity::FAILURE, Channel::MEMORY, "Failed to allocate memory for one of the pools");
			exit(EXIT_FAILURE);
		}

		for (size_t i = 0, j = 0; i < m_totalBytesAllocatedForPool; i += m_blockSizeInBytes, ++j) {

			uint32_t* lv_tempArray = reinterpret_cast<uint32_t*>(&m_array[i]);
			lv_tempArray[0] = m_gaurdValue;
			lv_tempArray[1] = (uint32_t)(j+1);

		}

		auto lv_sizeOfAllBlocksExceptLast = m_totalBytesAllocatedForPool - m_blockSizeInBytes;
		uint32_t* lv_lastBlock = reinterpret_cast<uint32_t*>(&m_array[lv_sizeOfAllBlocksExceptLast]);
		lv_lastBlock[1] = UINT32_MAX;

	}



	void* MemoryPool::Allocate()
	{
		using namespace LogSystem;

		if (nullptr == m_array) {
			LOG(Severity::INFO, Channel::MEMORY, "Could not allocate from pool due to the pool array being nullptr.");
			return nullptr;
		}

		if (0U == m_totalNumFreeList || UINT32_MAX == m_headHandleOfFreeList) {
			LOG(Severity::INFO, Channel::MEMORY, "There are no free blocks in the pool.");
			return nullptr;
		}


		uint32_t* lv_blockToReturn = reinterpret_cast<uint32_t*>(&m_array[m_blockSizeInBytes * m_headHandleOfFreeList]);

		if (m_gaurdValue != lv_blockToReturn[0]) {
			LOG(Severity::FAILURE, Channel::MEMORY, "Leakage of memory happened from before in the pool.");
			exit(EXIT_FAILURE);
		}

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
			
			char* lv_currentBlock = reinterpret_cast<char*>(l_block);

			size_t lv_totalNumBytesInBetween = lv_currentBlock - m_array;

			uint32_t lv_blockToBeFreedHandle = static_cast<uint32_t>(lv_totalNumBytesInBetween / m_blockSizeInBytes);

			uint32_t* lv_currentBlockUint32 = reinterpret_cast<uint32_t*>(l_block);

			lv_currentBlockUint32[0] = m_gaurdValue;
			lv_currentBlockUint32[1] = m_headHandleOfFreeList;
			m_headHandleOfFreeList = lv_blockToBeFreedHandle;
			++m_totalNumFreeList;
			return true;

		}
		else {

			LOG(Severity::FAILURE, Channel::MEMORY, "Memory that was requested to be deallocated from the pool was not in the range of the pool");
			exit(EXIT_FAILURE);

		}

	}

	MemoryPool::~MemoryPool()
	{
		delete[] m_array;
	}


}