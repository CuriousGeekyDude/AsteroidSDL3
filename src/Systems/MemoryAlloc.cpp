





#include "Systems/MemoryAloc.hpp"


namespace Asteroid
{


	MemoryAlloc::MemoryAlloc()
		: m_pool16(8192, 16)
		, m_pool32(8192, 32)
		, m_pool64(8192, 64)
		, m_pool128(8192, 128)
		, m_pool256(8192, 256)
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
		else if (l_blockSize <= 64) {
			return m_pool64.Allocate();
		}
		else if (l_blockSize <= 128) {
			return m_pool128.Allocate();
		}
		else if (l_blockSize <= 256) {
			return m_pool256.Allocate();
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
		else if (l_blockSize <= 64) {
			return m_pool64.Deallocate(l_block);
		}
		else if (l_blockSize <= 128) {
			return m_pool128.Deallocate(l_block);
		}
		else if (l_blockSize <= 256) {
			return m_pool256.Deallocate(l_block);
		}
		else {

			LOG(Severity::WARNING, Channel::MEMORY, "The requested blocksize to deallocate has not been allocated in any of the pools: Too big for it to fit in any of the blocks of the pools.");
			return false;
		}

	}


}