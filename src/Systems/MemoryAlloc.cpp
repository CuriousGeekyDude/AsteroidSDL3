





#include "Systems/MemoryAlloc.hpp"


namespace Asteroid
{


	MemoryAlloc::MemoryAlloc()
		: m_pool16(8192, 16)
		, m_pool32(8192, 32)
		, m_pool48(131072, 48)
		, m_pool64(131072, 64)
		, m_pool80(1024, 80)
		, m_pool96(2048, 96)
	{

	}



	void* MemoryAlloc::Allocate(const size_t l_blockSize)
	{

		if (l_blockSize <= 16) {
			return m_pool16.Allocate();
		}
		else if (l_blockSize <= 32) {
			return m_pool32.Allocate();
		}
		else if (l_blockSize <= 48) {
			return m_pool48.Allocate();
		}
		else if (l_blockSize <= 64) {
			return m_pool64.Allocate();
		}
		else if (l_blockSize <= 80) {
			return m_pool80.Allocate();
		}
		else if (l_blockSize <= 96) {
			return m_pool96.Allocate();
		}


		return nullptr;


	}



	bool MemoryAlloc::Deallocate(void* l_block, const size_t l_blockSize)
	{

		using namespace LogSystem;

		if (l_blockSize <= 16) {
			return m_pool16.Deallocate(l_block);
		}
		else if (l_blockSize <= 32) {
			return m_pool32.Deallocate(l_block);
		}
		else if (l_blockSize <= 48) {
			return m_pool48.Deallocate(l_block);
		}
		else if (l_blockSize <= 64) {
			return m_pool64.Deallocate(l_block);
		}
		else if (l_blockSize <= 80) {
			return m_pool80.Deallocate(l_block);
		}
		else if (l_blockSize <= 96) {
			return m_pool96.Deallocate(l_block);
		}
		else {

			LOG(Severity::WARNING, Channel::MEMORY, "The requested blocksize to deallocate has not been allocated in any of the pools: Too big for it to fit in any of the blocks of the pools.");
			return false;
		}

	}


}