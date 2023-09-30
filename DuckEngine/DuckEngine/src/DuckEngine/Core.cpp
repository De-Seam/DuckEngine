#include "Core.h"

#include "Utils/FMath.h"

#include <iostream>
#include <cassert>
#include <utility>
#include <windows.h>
#include <stdio.h>

std::string output_log = std::string("", 8192);

enum ConsoleColor : int32_t {
	console_color_white = 15,
	console_color_yellow = 14,
	console_color_red = 4,
	console_color_red_white = 0x0040 + 15
};

void SetConsoleColor(int32_t color)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
}

namespace DE
{
	void Log(const char* fmt ...)
	{
		va_list args;
		va_start(args, fmt);
		Internal::Log(LogType::Info, fmt, args);
		va_end(args);
	}

	void Log(LogType log_type, const char* fmt ...)
	{
		va_list args;
		va_start(args, fmt);
		Internal::Log(log_type, fmt, args);
		va_end(args);
	}

	namespace Internal
	{
		void Log(LogType log_type, const char* fmt, va_list args)
		{
			std::string msg;
			msg.reserve(128);

			switch (log_type)
			{
			case LogType::Info:
				msg = "[INFO] ";
				SetConsoleColor(ConsoleColor::console_color_white);
				break;
			case LogType::Message:
				msg = "[MESSAGE] ";
				SetConsoleColor(ConsoleColor::console_color_white);
				break;
			case LogType::Warning:
				msg = "[WARNING] ";
				SetConsoleColor(ConsoleColor::console_color_yellow);
				break;
			case LogType::Error:
				msg = "[ERROR] ";
				SetConsoleColor(ConsoleColor::console_color_red);
				break;
			}

			//va_start(args, fmt);

			while (*fmt != '\0') {

				if (*fmt == '%')
				{
					++fmt;
					if (*fmt == 'i' || *fmt == 'I') {
						int i = va_arg(args, int);
						msg += std::to_string(i);
					}
					else if (*fmt == 'u' || *fmt == 'U') {
						u32 i = va_arg(args, u32);
						msg += std::to_string(i);
					}
					else if (*fmt == 'f' || *fmt == 'F') {
						double f = va_arg(args, double);
						msg += std::to_string(f);
					}
					else if (*fmt == 'c' || *fmt == 'C') {
						const char c = va_arg(args, char);
						msg += c;
					}
					else if (*fmt == 's' || *fmt == 'S') {
						std::string s = va_arg(args, const char*);
						msg += s;
					}
					else if (*fmt == 'v' || *fmt == 'V')
					{
						++fmt;
						if (*fmt == '2') {
							fm::vec2 v2 = va_arg(args, fm::vec2);
							msg += std::to_string(v2.x) + ", " + std::to_string(v2.y);
						}
						else if (*fmt == '3') {
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

			//va_end(args);

			msg += '\n';
			std::cout << msg;
			output_log += msg;

			SetConsoleColor(ConsoleColor::console_color_white);
		}

		std::string& GetLog()
		{
			return output_log;
		}
	}
}