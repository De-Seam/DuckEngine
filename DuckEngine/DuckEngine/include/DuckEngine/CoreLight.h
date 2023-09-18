#pragma once
#include "Utils/Variables.h"

#ifdef DUCK_EXPORTS
#define DUCK_API __declspec(dllexport)
#else
#define DUCK_API __declspec(dllimport)
#endif

#include <string>

namespace DE //Duck Engine
{
	enum class LogType
	{
		Info,
		Message,
		Warning,
		Error
	};

	DUCK_API void Log(const char* fmt...);
	DUCK_API void Log(LogType log_type, const char* fmt...);

	namespace Internal //Internal
	{
		DUCK_API void Log(LogType log_type, const char* fmt, va_list args);
		DUCK_API std::string& GetLog();
	}
}