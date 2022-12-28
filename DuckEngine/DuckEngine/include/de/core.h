#pragma once

#ifdef DUCK_EXPORTS
#define DUCK_API __declspec(dllexport)
#else
#define DUCK_API __declspec(dllimport)
#endif

#include "utils/variables.h"
#include "utils/uid.h"
#include "engine/object.h"

#include <string>

namespace de //Duck Engine
{
	enum class LogType
	{
		info,
		message,
		warning,
		error
	};

	DUCK_API void log(const char* fmt...);
	DUCK_API void log(LogType log_type, const char* fmt...);

	namespace internal //Internal
	{
		DUCK_API void log(LogType log_type, const char* fmt, va_list args);
		DUCK_API std::string& get_log();
	}
}