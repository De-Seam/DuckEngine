#include "da/app/app.h"
#include "da/editor/editor.h"

#include "de/engine/engine.h"

#include <chrono>

namespace da //DuckApp
{
	bool App::m_is_running = false;
	f32 App::m_delta_time = F32_EPSILON;

	void App::init()
	{
		de::Engine::init();
		main_loop();
	}

	void App::main_loop()
	{
		m_is_running = true;
		auto current_time = std::chrono::steady_clock::now();

		while(m_is_running)
		{
			auto start = std::chrono::steady_clock::now();

			update(m_delta_time);

			auto end = std::chrono::steady_clock::now();
			std::chrono::duration<f32> elapsed_chrono_time = end - start;
			m_delta_time = elapsed_chrono_time.count();
		}
	}

	void App::update(f32 dt)
	{
		de::Engine::begin_frame();

		de::Engine::update(m_delta_time);

		de::Engine::end_frame();
	}
}