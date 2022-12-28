#pragma once
#include "de/core.h"
#include "de/engine/object.h"
#include "de/engine/game_instance.h"

#include <phmap/phmap.h>

namespace de //DuckEngine
{
	class World;

	class DUCK_API Engine
	{
	public:
		static void init(); //Initialize engine
		static void shutdown(); //Clean Shutdown

		static void set_game_instance(GameInstance* game_instance);

		static void begin_frame(); //Begin frame
		static void update(f32 dt); //Update game
		static void end_frame(); //End frame

		static f32 get_delta_time() { return m_delta_time; }
		static bool get_is_running() { return m_is_running; }
	private:
		static void shutdown_internal(); //Actual shutdown logic
		static void add_object(Object* object); //For objects to add themselves

	private:
		static bool m_is_running;
		static f32 m_delta_time;

		static phmap::flat_hash_map<UID, Object*> m_objects;

		static GameInstance* m_game_instance;
		static World* m_world;

		friend class Object;
	};
}