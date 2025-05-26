#pragma once





#include "Systems/MemoryPool.hpp"



namespace Asteroid
{


	class MemoryAlloc final
	{

	public:

		MemoryAlloc();


		void* Allocate(const size_t l_blockSize);



		template<typename T>
		void Destruct(T* l_block, const size_t l_sizeOfBlock)
		{
			if (nullptr == l_block) {
				return;
			}

			l_block->~T();
			
			Deallocate(l_block, l_sizeOfBlock);
		}

	private:

		bool Deallocate(void* l_block, const size_t l_sizeOfBlock);


	private:

		MemoryPool m_pool16;
		MemoryPool m_pool32;
		MemoryPool m_pool64;
		MemoryPool m_pool128;
		MemoryPool m_pool256;

	};

}