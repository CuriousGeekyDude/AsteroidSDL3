#pragma once



#include <Windows.h>
#include <format>
#include <string_view>
#include <array>

namespace Asteroid
{

	namespace LogSystem
	{

		enum class Severity
		{
			FAILURE = 0,
			WARNING,
			INFO
		};

		enum class Channel
		{
			GRAPHICS = 0,
			PHYSICS,
			INITIALIZATION
		};


		wchar_t* ConvertCharToWchar(const char* l_string);

		static Severity lv_possibleCurrentLevel{ Severity::INFO };


		void UpdateToCurrentVerbosity();
		void SetVerbosity(const Severity l_level);


		int ConstructFinalMsg(char* const l_finalMsg, const char* const l_formattedMsg, size_t l_sizeOfFinalMsg
			, va_list l_argList);


		//This function ,in addition to preparing for construction of a log message,
		// is also used to set the severity since it has the current
		// severity as a static variable
		const char* PrepareAndConstructLogMsg(const Severity l_level, const Channel l_category
			, const int l_lineNumber, const char* l_filePath, const char* l_userMsg
			, va_list l_argList);

		void PrintCmd(const char* l_msg);

		void PrintVisualStdConsole(const char* l_msg);


		void Log(const Severity l_level, const Channel l_category
			, const int l_lineNumber, const char* l_filePath
			, const char* l_userMsg, ...);

	}


#ifdef LOGGING

#define LOG(l_level, l_category, l_userMsg, ...) LogSystem::Log(l_level, l_category, __LINE__, __FILE__, l_userMsg, __VA_ARGS__);

#define Set_Verbosity(l_level) LogSystem::SetVerbosity(l_level);
#else

#define LOG(l_level, l_category, l_userMsg, ...)
#define Set_Verbosity(l_level)

#endif


}