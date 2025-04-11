




#include "Systems/LogSystem.hpp"
#include <cassert>
#include <array>
#include <fstream>


namespace Asteroid
{
	namespace LogSystem
	{
		wchar_t* ConvertCharToWchar(const char* l_string)
		{
			constexpr uint32_t lv_maxSizeMsg{ 2048 };
			static wchar_t lv_finalMsg[lv_maxSizeMsg];

			memset(&lv_finalMsg, 0, sizeof(wchar_t) * lv_maxSizeMsg);

			size_t lv_totalNumCharConverted{};
			assert(0 == mbstowcs_s<lv_maxSizeMsg>
				(&lv_totalNumCharConverted, lv_finalMsg, l_string
					, lv_maxSizeMsg - 1));

			return lv_finalMsg;
		}


		
		int ConstructFinalMsg(char* const l_finalMsg, const char* const l_formattedMsg
			, size_t l_sizeOfFinalMsg,va_list l_argList)
		{
			int lv_numberCharsWritten = vsnprintf(l_finalMsg, l_sizeOfFinalMsg, l_formattedMsg, l_argList);

			return lv_numberCharsWritten;
		}

		const char* PrepareAndConstructLogMsg(const Severity l_level, const Channel l_category
			, const int l_lineNumber, const char* l_filePath, const char* l_userMsg, va_list l_argList)
		{
			constexpr size_t lv_finalMsgSize{ 2028 };
			static char lv_finalMsg[lv_finalMsgSize];
			static char lv_formattedMsg[lv_finalMsgSize];
			static Severity lv_currentVerbosity = Severity::INFO;


			if (nullptr == l_userMsg) {
				return nullptr;
			}

			//Setting verbosity
			if (-1 == l_lineNumber) {
				lv_currentVerbosity = l_level;
				return nullptr;
			}

			if (-2 == l_lineNumber) {
				lv_possibleCurrentLevel = lv_currentVerbosity;
				return nullptr;
			}

			memset(&lv_formattedMsg, 0, sizeof(char) * lv_finalMsgSize);
			memset(&lv_finalMsg, 0, sizeof(char) * lv_finalMsgSize);

			char lv_templatePartOfMsg1[] = "\n\n---------------------------\n\n[%s] [%s] [line %d in file %s]: ";
			
			constexpr uint32_t lv_remainingSizeFinalMsg = lv_finalMsgSize - (sizeof(lv_templatePartOfMsg1) / sizeof(char));

			

			memcpy(&lv_formattedMsg, &lv_templatePartOfMsg1, sizeof(lv_templatePartOfMsg1));

			std::array<char, 64> lv_severity{};
			if (Severity::FAILURE == l_level) {
				char lv_tempSeverity[] = "FAILURE";
				memcpy(lv_severity.data(), &lv_tempSeverity, sizeof(lv_tempSeverity));
			}
			if (Severity::WARNING == l_level) {
				char lv_tempSeverity[] = "WARNING";
				memcpy(lv_severity.data(), &lv_tempSeverity, sizeof(lv_tempSeverity));
			}
			if (Severity::INFO == l_level) {
				char lv_tempSeverity[] = "INFO";
				memcpy(lv_severity.data(), &lv_tempSeverity, sizeof(lv_tempSeverity));
			}


			std::array<char, 64> lv_channel{};
			if (Channel::GRAPHICS == l_category) {
				char lv_tempChannel[] = "GRAPHICS";
				memcpy(lv_channel.data(), &lv_tempChannel, sizeof(lv_tempChannel));
			}
			if (Channel::INITIALIZATION == l_category) {
				char lv_tempChannel[] = "INITIALIZATION";
				memcpy(lv_channel.data(), &lv_tempChannel, sizeof(lv_tempChannel));
			}
			if (Channel::PHYSICS == l_category) {
				char lv_tempChannel[] = "PHYSICS";
				memcpy(lv_channel.data(), &lv_tempChannel, sizeof(lv_tempChannel));
			}



			int lv_totalNumCharWritten = snprintf(lv_finalMsg, lv_finalMsgSize
				, lv_formattedMsg, lv_severity.data(), lv_channel.data(), l_lineNumber, l_filePath);

			if (-1 == lv_totalNumCharWritten) {
				OutputDebugString(L"snprintf() failed to produce formatted string for logging.\n");
				exit(EXIT_FAILURE);
			}

			size_t lv_totalFinalMsgFilled{};
			for (size_t i = 0; i < lv_finalMsgSize; ++i) {
				if ('\0' == lv_finalMsg[i]) {
					break;
				}
				++lv_totalFinalMsgFilled;
			}

			uint32_t lv_totalCharUserMsg{};
			for (uint32_t i = 0; i < lv_remainingSizeFinalMsg; ++i) {
				if ('\0' == l_userMsg[i]) {
					break;
				}
				++lv_totalCharUserMsg;
			}
			memcpy(&lv_finalMsg[lv_totalFinalMsgFilled], l_userMsg, (size_t)sizeof(char) * lv_totalCharUserMsg);

			lv_totalNumCharWritten = ConstructFinalMsg(lv_finalMsg, lv_finalMsg, lv_finalMsgSize, l_argList);
			

			if (-1 == lv_totalNumCharWritten) {
				OutputDebugString(L"ConstructFinalMsg() failed to produce formatted string for logging.\n");
				exit(EXIT_FAILURE);
			}

			return lv_finalMsg;
		}


		void SetVerbosity(const Severity l_level)
		{
			va_list lv_dummyList = nullptr;
			PrepareAndConstructLogMsg(l_level, Channel::INITIALIZATION, -1, nullptr, nullptr, lv_dummyList);
		}

		void UpdateToCurrentVerbosity()
		{
			va_list lv_dummyList = nullptr;
			PrepareAndConstructLogMsg(Severity::INFO, Channel::INITIALIZATION, -2, nullptr, nullptr, lv_dummyList);

		}

		void PrintCmd(const char* l_msg)
		{
			printf(l_msg);
		}

		void PrintVisualStdConsole(const char* l_msg)
		{
			OutputDebugString(ConvertCharToWchar(l_msg));
		}

		void Log(const Severity l_level, const Channel l_category
			, const int l_lineNumber, const char* l_filePath
			, const char* l_userMsg,...)
		{
			static std::ofstream lv_logFile{};
			static uint64_t lv_counter{};

			if (0 == lv_counter) {
				lv_logFile.open("Logging/LogFile.txt", std::ofstream::trunc);
			}
			else {
				lv_logFile.open("Logging/LogFile.txt", std::ofstream::app);
			}


			va_list lv_argList;
			va_start(lv_argList, l_userMsg);
			const char* lv_msg = PrepareAndConstructLogMsg(l_level, l_category, l_lineNumber, l_filePath, l_userMsg, lv_argList);
			va_end(lv_argList);

			if (nullptr == lv_msg) { return; }

			UpdateToCurrentVerbosity();

			if ((int)l_level <= (int)lv_possibleCurrentLevel) {
				PrintCmd(lv_msg);
				PrintVisualStdConsole(lv_msg);
			}
			lv_logFile << lv_msg << "\n";
			lv_logFile.flush();
			lv_logFile.close();
			++lv_counter;
		}

	}

}