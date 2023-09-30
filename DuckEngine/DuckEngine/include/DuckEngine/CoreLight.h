#pragma once
#include "Utils/Variables.h"

#include <string>

#ifdef DUCK_EDITOR
#define EDITOR_ONLY(x) x
#else
#define EDITOR_ONLY(x)
#endif

namespace DE //Duck Engine
{
enum class LogType
{
	Info,
	Message,
	Warning,
	Error
};

void Log(const char* fmt...);
void Log(LogType log_type, const char* fmt...);

namespace Internal //Internal
{
	void Log(LogType log_type, const char* fmt, va_list args);
	std::string& GetLog();
}
}
