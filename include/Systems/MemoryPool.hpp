#pragma once






#include <cinttypes>

namespace Asteroid
{


	class MemoryPool final
	{
	public:

		//Block size is assumed to always be multiple of 16.

		/* Bytes requested to allocate should always be power of 2.
		* If it is not then it will be rounded up to the smallest power of 2 
		* bigger than the requested size.
		*/

		MemoryPool(const size_t l_minBytesToAllocate, const size_t l_blockSizes);
		

		/*
		* The returned void* is going to be cast to the type by the user and modified 
		* through the course of the program. That naturally violates strict aliasing rule
		* that compiler assumes us to respect when doing optimizations. 
		* One way to respect this rule and still do type punning is to use memcpy().
		* But due to how much refactoring that required, we wont respect that rule 
		* and just build the project without optimization flags turned on.
		*/
		void* Allocate();


		MemoryPool(const MemoryPool&) = delete;
		MemoryPool& operator=(const MemoryPool&) = delete;


		bool Deallocate(void* l_block);



		~MemoryPool();

	private:

		static constexpr uint32_t m_gaurdDebugValue{ 0x12345678 };

		size_t m_blockSizeInBytes;

		unsigned char* m_array{ nullptr };
		size_t m_totalBytesAllocatedForPool{ 0U };

		uint32_t m_headHandleOfFreeList{0U};
		uint32_t m_totalNumFreeList{0U};


	};


}