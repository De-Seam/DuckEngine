#include "de/core.h"

#include <iostream>
#include <cassert>
#include <utility>
#include <windows.h>
#include <stdio.h>

namespace de //DuckEngine
{
	std::string output_log = std::string("", 8192);

	enum ConsoleColor : int32_t {
		console_color_white = 15,
		console_color_yellow = 14,
		console_color_red = 4,
		console_color_red_white = 0x0040 + 15
	};

	void set_console_color(int32_t color)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, static_cast<WORD>(color));
	}

	void log(const char* fmt ...)
	{
		va_list args;
		va_start(args, fmt);
		internal::log(LogType::info, fmt, args);
		va_end(args);
	}

	void log(LogType log_type, const char* fmt ...)
	{
		va_list args;
		va_start(args, fmt);
		internal::log(log_type, fmt, args);
		va_end(args);
	}

	namespace internal
	{
		void log(LogType log_type, const char* fmt, va_list args)
		{
			std::string msg;

			switch(log_type)
			{
			case LogType::info:
				msg = "[INFO] ";
				set_console_color(ConsoleColor::console_color_white);
				break;
			case LogType::message:
				msg = "[MESSAGE] ";
				set_console_color(ConsoleColor::console_color_white);
				break;
			case LogType::warning:
				msg = "[WARNING] ";
				set_console_color(ConsoleColor::console_color_yellow);
				break;
			case LogType::error:
				msg = "[ERROR] ";
				set_console_color(ConsoleColor::console_color_red);
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
					else if (*fmt == 'f' || *fmt == 'F') {
						double f = va_arg(args, double);
						msg += std::to_string(f);
					}
					else if (*fmt == 'c' || *fmt == 'C') {
						const char c = va_arg(args, char);
						msg += c;
					}
					else if (*fmt == 's' || *fmt == 'S') {
						std::string s = va_arg(args, char*);
						msg += s;
					}

					//if (*fmt == 'v' || *fmt == 'V')
					//{
					//	++fmt;
					//	if (*fmt == '2') {
					//		glm::vec2 v2 = va_arg(args, glm::vec2);
					//		msg += std::to_string(v2.x) + ", " + std::to_string(v2.y);
					//	}
					//	else if (*fmt == '3') {
					//		glm::vec3 v3 = va_arg(args, glm::vec3);
					//		msg += std::to_string(v3.x) + ", " + std::to_string(v3.y) + ", " + std::to_string(v3.z);
					//	}
					//}
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

			set_console_color(ConsoleColor::console_color_white);
		}

		std::string& get_log()
		{
			return output_log;
		}
	}
}