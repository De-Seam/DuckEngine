#pragma once
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
	Warning,
	Error
};

void Log(const char* fmt...);
void Log(LogType log_type, const char* fmt...);
}
