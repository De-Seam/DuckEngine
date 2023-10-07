#pragma once
#include "DuckEngine/Core.h"
#include "DuckEngine/Utils/SafeQueue.h"

#include <thread>


namespace DE
{
struct LogQueueItem
{
	LogType logType;
	std::string msg;
};

class LogManager
{
public:
	static void Init();
	static void Cleanup();

	static void Log(LogType logType, const char* fmt...);
	static void Log(LogType logType, const char* fmt, va_list args);

	enum class ConsoleColor : i32
	{
		White = 15,
		Yellow = 14,
		Red = 4,
		RedWhite = 0x0040 + 15
	};

	static void SetConsoleColor(i32 color);

	static const std::string& GetLog() { return m_outputLog; }
	static void SetLogFilePath(const std::string& filePath);
	static void SetLogFileName(const std::string& fileName);

private:
	static void LogThreadLoop();

	static bool m_threadRunning;
	static std::thread m_logThread;
	static SafeQueue<LogQueueItem> m_logQueue;

	static std::string m_outputLog;
	static std::string m_logFilePath;
	static std::string m_logFileName;
};
}
