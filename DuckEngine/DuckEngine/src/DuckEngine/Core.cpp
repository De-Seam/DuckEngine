#include "Core.h"

#include "DuckEngine/Engine/LogManager.h"

#include <windows.h>

namespace DE
{
void Log(const char* fmt ...)
{
	va_list args;
	va_start(args, fmt);
	LogManager::Log(LogType::Info, fmt, args);
	va_end(args);
}

void Log(LogType log_type, const char* fmt ...)
{
	va_list args;
	va_start(args, fmt);
	LogManager::Log(log_type, fmt, args);
	va_end(args);
}
}
