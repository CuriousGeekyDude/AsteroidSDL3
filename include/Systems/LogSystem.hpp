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

		

		void SetVerbosity(const Severity l_level);

		//This function ,in addition to constructing a log message,
		// is also used to set the severity since it has the current
		// severity as a static variable
		const char* ConstructLogMsg(const Severity l_level, const Channel l_category
			, const int l_lineNumber, const char* l_filePath, const char* l_userMsg
			, const char* l_extraMsg = nullptr);

		void PrintCmd(const char* l_msg);

		void PrintVisualStdConsole(const char* l_msg);


		void Log(const Severity l_level, const Channel l_category
			, const int l_lineNumber, const char* l_filePath
			, const char* l_userMsg, const char* l_extraMsg = nullptr);

	}


#ifdef LOGGING

#define LOG(l_level, l_category, l_userMsg, l_extraMsg) LogSystem::Log(l_level, l_category, __LINE__, __FILE__, l_userMsg, l_extraMsg);

#define Set_Verbosity(l_level) LogSystem::SetVerbosity(l_level);
#else

#define LOG(l_level, l_category, l_userMsg, l_extraMsg)
#define Set_Verbosity(l_level)

#endif


}