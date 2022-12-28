#include "de/events/sdl_event_manager.h"
#include "de/engine/engine.h"
#include "de/utils/fmath.h"

namespace de
{
	std::vector<SDLEventFunction> SDLEventManager::m_event_functions_all = {};
	phmap::flat_hash_map<SDL_EventType,std::vector<SDLEventFunction>> SDLEventManager::m_event_functions = {};

	void SDLEventManager::remove_event_function(UID uid)
	{
		SDLEventFunction* event_function = static_cast<SDLEventFunction*>(Engine::get_object(uid));
		for(size_t i = 0; i < m_event_functions_all.size(); i++)
		{
			if(m_event_functions_all[i].uid = event_function->uid)
			{
				fm::swap(m_event_functions_all[i], m_event_functions_all.back());
				m_event_functions_all.pop_back();
			}
		}
		std::vector<SDLEventFunction>& event_functions = m_event_functions[event_function->event_type];
		for(size_t i = 0; i < event_functions.size(); i++)
		{
			if(event_functions[i].uid = event_function->uid)
			{
				fm::swap(event_functions[i], event_functions.back());
				event_functions.pop_back();
			}
		}
	}

	UID SDLEventManager::add_event_function(SDLEventFunction event_function, bool all_events)
	{
		if(all_events)
			m_event_functions_all.emplace_back(event_function);
		else
			m_event_functions[event_function.event_type].emplace_back(event_function);

		return event_function.uid;
	}

	void SDLEventManager::update()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			for(SDLEventFunction& event_function : m_event_functions_all)
				event_function.function_ptr(event);

			std::vector<SDLEventFunction>& event_array = m_event_functions[static_cast<SDL_EventType>(event.type)];
			for(SDLEventFunction& event_function : event_array)
				event_function.function_ptr(event);
		}
	}
}