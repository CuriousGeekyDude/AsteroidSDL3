#pragma once






#include <cinttypes>
#include "Systems/LogSystem.hpp"
#include <numeric>

namespace Asteroid
{


	class MemoryPool final
	{
	public:

		MemoryPool(const size_t l_minBytesToAllocate, const size_t l_blockSizes);
		

		void* Allocate();


		bool Deallocate(void* l_block);



		~MemoryPool();

	private:

		const size_t m_blockSizeInBytes;
		static constexpr uint32_t m_gaurdValue{(uint32_t)0x12345678};

		char* m_array{ nullptr };
		size_t m_totalBytesAllocatedForPool{ 0 };

		uint32_t m_headHandleOfFreeList{0U};
		uint32_t m_totalNumFreeList{0U};
		uint32_t m_totalNumAllocatedBlocks{0U};


	};


}