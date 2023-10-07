#include "DuckEngine/Engine/LogManager.h"

#include <cstdarg>
#include <SDL/SDL_syswm.h>

namespace DE
{
bool LogManager::m_threadRunning = false;
std::thread LogManager::m_logThread = {};
SafeQueue<LogQueueItem> LogManager::m_logQueue = {};

std::string LogManager::m_outputLog;
std::string LogManager::m_logFilePath;
std::string LogManager::m_logFileName;

void LogManager::Init()
{
	m_outputLog.reserve(8192);

	m_logThread = std::thread(LogThreadLoop);
}

void LogManager::Cleanup()
{
	m_threadRunning = false;
	m_logThread.join();
}

void LogManager::Log(LogType logType, const char* fmt ...)
{
	va_list args;
	va_start(args, fmt);
	Log(logType, fmt, args);
	va_end(args);
}

void LogManager::Log(LogType logType, const char* fmt, va_list args)
{
	std::string msg;
	msg.reserve(128);

	switch (logType)
	{
	case LogType::Info:
		msg = "[INFO] ";
		break;
	case LogType::Warning:
		msg = "[WARNING] ";
		break;
	case LogType::Error:
		msg = "[ERROR] ";
		break;
	}

	while (*fmt != '\0')
	{
		if (*fmt == '%')
		{
			++fmt;
			if (*fmt == 'i' || *fmt == 'I')
			{
				int i = va_arg(args, int);
				msg += std::to_string(i);
			}
			else if (*fmt == 'u' || *fmt == 'U')
			{
				u32 i = va_arg(args, u32);
				msg += std::to_string(i);
			}
			else if (*fmt == 'f' || *fmt == 'F')
			{
				double f = va_arg(args, double);
				msg += std::to_string(f);
			}
			else if (*fmt == 'c' || *fmt == 'C')
			{
				const char c = va_arg(args, char);
				msg += c;
			}
			else if (*fmt == 's' || *fmt == 'S')
			{
				std::string s = va_arg(args, const char*);
				msg += s;
			}
			else if (*fmt == 'v' || *fmt == 'V')
			{
				++fmt;
				if (*fmt == '2')
				{
					fm::vec2 v2 = va_arg(args, fm::vec2);
					msg += std::to_string(v2.x) + ", " + std::to_string(v2.y);
				}
				else if (*fmt == '3')
				{
					fm::vec3 v3 = va_arg(args, fm::vec3);
					msg += std::to_string(v3.x) + ", " + std::to_string(v3.y) + ", " + std::to_string(v3.z);
				}
			}
		}
		else
		{
			msg += *fmt;
		}
		++fmt;
	}

	msg += '\n';

	LogQueueItem logQueueItem = {logType, msg};
	m_logQueue.enqueue(logQueueItem);
}

void LogManager::SetConsoleColor(i32 color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
}

void LogManager::SetLogFilePath(const std::string& filePath)
{
	m_logFilePath = filePath;
}

void LogManager::SetLogFileName(const std::string& fileName)
{
	m_logFileName = fileName;
}

void LogManager::LogThreadLoop()
{
	m_threadRunning = true;
	while (m_threadRunning)
	{
		LogQueueItem queueItem = m_logQueue.dequeue();

		switch (queueItem.logType)
		{
		case LogType::Info:
			SetConsoleColor(static_cast<i32>(ConsoleColor::White));
			break;
		case LogType::Warning:
			SetConsoleColor(static_cast<i32>(ConsoleColor::Yellow));
			break;
		case LogType::Error:
			SetConsoleColor(static_cast<i32>(ConsoleColor::Red));
			break;
		}

		std::cout << queueItem.msg;
		m_outputLog += queueItem.msg;

		SetConsoleColor(static_cast<i32>(ConsoleColor::White));
	}
}
}
