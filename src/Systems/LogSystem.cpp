




#include "Systems/LogSystem.hpp"
#include <string>
#include <cassert>


namespace Asteroid
{
	namespace LogSystem
	{
		std::wstring ConvertCharToWchar(const std::string& l_string)
		{
			constexpr uint32_t lv_maxSizeMsg{ 2048 };

			size_t lv_totalNumCharConverted{};
			wchar_t lv_finalMsg[lv_maxSizeMsg];

			assert(0 == mbstowcs_s<lv_maxSizeMsg>
				(&lv_totalNumCharConverted, lv_finalMsg, l_string.data()
					, lv_maxSizeMsg-1));

			return std::wstring{lv_finalMsg};
		}
	}
}