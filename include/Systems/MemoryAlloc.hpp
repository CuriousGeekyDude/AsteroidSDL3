#pragma once





#include "Systems/MemoryPool.hpp"
#include "Systems/LogSystem.hpp"


namespace Asteroid
{


	class MemoryAlloc final
	{

	public:

		MemoryAlloc();


		void* Allocate(const size_t l_blockSize);



		template<typename T>
		bool Destruct(T* l_block, const size_t l_sizeOfBlock)
		{
			if (nullptr == l_block) {
				LOG(Severity::WARNING, Channel::MEMORY, "Tried to destruct a nullptr.");
				return false;
			}

			l_block->~T();
			
			return Deallocate(l_block, l_sizeOfBlock);
		}

	private:

		bool Deallocate(void* l_block, const size_t l_sizeOfBlock);


	private:

		MemoryPool m_pool16;
		MemoryPool m_pool32;
		MemoryPool m_pool48;
		MemoryPool m_pool64;
		MemoryPool m_pool80;
		MemoryPool m_pool96;

	};

}