#include "de/engine/engine.h"
#include "de/renderer/renderer.h"
#include "de/entity/entity.h"
#include "de/world/world.h"
#include "de/events/sdl_event_manager.h"

namespace de
{
	bool Engine::m_is_running = false;
	f32 Engine::m_delta_time = F32_EPSILON;

	phmap::flat_hash_map<UID, Object*> Engine::m_objects = {};

	GameInstance* Engine::m_game_instance = nullptr;

	void Engine::init()
	{
		Renderer::init();

		SDLEventFunction shutdown_event;
		shutdown_event.event_type = SDL_EventType::SDL_QUIT;
		shutdown_event.function_ptr = 
		{ [](SDL_Event& event)
		{
			Engine::shutdown();
		}};
		SDLEventManager::add_event_function(shutdown_event);
		
		m_is_running = true;
	}

	void Engine::shutdown()
	{
		m_is_running = false;
	}

	void Engine::internal_begin_play()
	{
		m_game_instance->begin_play();
	}

	void Engine::set_game_instance(GameInstance* game_instance)
	{
		delete m_game_instance;
		m_game_instance = game_instance;
	}

	void Engine::begin_frame()
	{
		Renderer::begin_frame();
	}

	void Engine::update(f32 dt)
	{
		m_delta_time = dt;
		SDLEventManager::update();

		m_game_instance->update(dt);
	}

	void Engine::end_frame()
	{
		Renderer::end_frame();
	}

	Object* Engine::get_object(UID uid)
	{
		return m_objects[uid];
	}

	void Engine::shutdown_internal()
	{
		Renderer::shutdown();

		exit(EXIT_SUCCESS);
	}

	void Engine::add_object(Object* object)
	{
		m_objects[object->uid] = object;
	}

	void Engine::remove_object(Object* object)
	{
		m_objects.erase(object->uid);
	}
}