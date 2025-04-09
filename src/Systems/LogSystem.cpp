




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





		const char* ConstructLogMsg(const Severity l_level, const Channel l_category
			, const int l_lineNumber, const char* l_filePath, const char* l_userMsg, const char* l_extraMsg)
		{
			constexpr size_t lv_finalMsgSize{ 2028 };
			static char lv_finalMsg[lv_finalMsgSize];
			static char lv_formattedMsg[lv_finalMsgSize];
			static Severity lv_currentVerbosity = Severity::INFO;


			//Setting verbosity
			if (-1 == l_lineNumber) {
				lv_currentVerbosity = l_level;
				return nullptr;
			}

			memset(&lv_formattedMsg, 0, sizeof(char) * lv_finalMsgSize);
			memset(&lv_finalMsg, 0, sizeof(char) * lv_finalMsgSize);

			if ((int)l_level < (int)lv_currentVerbosity) { return nullptr; }

			char lv_templatePartOfMsg1[] = "\n\n---------------------------\n\n[%s] [%s] [line %d in file %s]: %s\n";
			char lv_templatePartOfMsg2[] = "\n\n---------------------------\n\n[%s] [%s] [line %d in file %s]: %s : %s \n";


			if (nullptr == l_userMsg) {
				return nullptr;
			}
			if (nullptr == l_extraMsg) {
				memcpy(&lv_formattedMsg, &lv_templatePartOfMsg1, sizeof(lv_templatePartOfMsg1) / sizeof(char));
			}
			else {
				memcpy(&lv_formattedMsg, &lv_templatePartOfMsg2, sizeof(lv_templatePartOfMsg2) / sizeof(char));
			}

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


			int lv_totalNumCharsWritten{};
			if (nullptr == l_extraMsg) {
				lv_totalNumCharsWritten = snprintf(lv_finalMsg, lv_finalMsgSize - 1, lv_formattedMsg, lv_severity.data(), lv_channel.data(), l_lineNumber, l_filePath, l_userMsg);
			}
			else {
				lv_totalNumCharsWritten = snprintf(lv_finalMsg, lv_finalMsgSize - 1, lv_formattedMsg, lv_severity.data(), lv_channel.data(), l_lineNumber, l_filePath, l_userMsg, l_extraMsg);
			}

			if (-1 == lv_totalNumCharsWritten) {
				OutputDebugString(L"snprintf() failed to produce formatted string for logging.\n");
				exit(EXIT_FAILURE);
			}

			return lv_finalMsg;
		}


		void SetVerbosity(const Severity l_level)
		{
			ConstructLogMsg(l_level, Channel::INITIALIZATION, -1, nullptr, nullptr);
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
			, const char* l_userMsg, const char* l_extraMsg)
		{
			static uint64_t lv_flushToFileCounter{};
			static std::ofstream lv_logFile{"Logging/LogFile.txt", std::ofstream::app | std::ofstream::trunc};
			const char* lv_msg = ConstructLogMsg(l_level, l_category, l_lineNumber, l_filePath, l_userMsg, l_extraMsg);
			if (nullptr == lv_msg) { return; }
			PrintCmd(lv_msg);
			PrintVisualStdConsole(lv_msg);
			lv_logFile << lv_msg << "\n";

			if (Severity::FAILURE == l_level || 0 == lv_flushToFileCounter % 10) { lv_logFile.flush(); }
			++lv_flushToFileCounter;
		}

	}

}