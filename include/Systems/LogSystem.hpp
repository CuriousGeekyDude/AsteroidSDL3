#pragma once



#include <Windows.h>
#include <format>
#include <string_view>
#include <string>


namespace Asteroid
{

	namespace LogSystem
	{


		std::wstring ConvertCharToWchar(const std::string& l_string);


		template<typename ...args>
		void LogVisualStudioConsole(const char* l_formattedMsg, args&& ...l_args)
		{
			if constexpr (0 == sizeof...(l_args)) {
				OutputDebugString(ConvertCharToWchar(l_formattedMsg).data());
			}
			else {


				std::string lv_constructMsg
				{"\n\n-------------------------------------------------------\n\n** [{0}] ** [{1}] ** [line {2} of file {3}]: "};
				lv_constructMsg += l_formattedMsg;

				std::string lv_formattedMsg = std::move(std::vformat(lv_constructMsg, std::make_format_args(l_args...)));

				OutputDebugString(ConvertCharToWchar(lv_formattedMsg).data());

			}
		}

		template<typename ...args>
		void LogCommandLine(const char* l_formattedMsg, args&& ... l_arg)
		{
			if constexpr (0 == sizeof...(l_arg)) {
				printf(l_formattedMsg);
			}
			else {

				std::string lv_constructMsg
				{ "\n\n-------------------------------------------------------\n\n** [{0}] ** [{1}] ** [line {2} of file {3}]: " };
				lv_constructMsg += l_formattedMsg;

				std::string lv_formattedMsg = std::move(std::vformat(lv_constructMsg, std::make_format_args(l_arg...)));

				printf(lv_formattedMsg.c_str());
			}
		}

	}


}