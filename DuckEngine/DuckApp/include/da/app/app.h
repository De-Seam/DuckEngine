#pragma once
#include "de/core.h"

namespace da //DuckApp
{
	class App
	{
	public:
		static void init();

	private:
		static void main_loop();
		static void update(f32 dt);

	private:
		static bool m_is_running;
		static f32 m_delta_time;
	};
}