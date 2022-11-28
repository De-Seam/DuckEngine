#pragma once
#include "de/core.h"

namespace de //DuckEngine
{
	class World;

	class DUCK_API Engine
	{
	public:
		static void init(); //Initialize engine
		static void shutdown(); //Clean Shutdown

		static void begin_frame(); //Begin frame
		static void update(f32 dt); //Update game
		static void end_frame(); //End frame

		static f32 get_delta_time() { return m_delta_time; }
		static bool get_is_running() { return m_is_running; }
	private:
		static void shutdown_internal(); //Actual shutdown logic

	private:
		static bool m_is_running;
		static f32 m_delta_time;

		static World* m_world;
	};
}