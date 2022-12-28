#include "de/events/sdl_event_manager.h"

namespace de
{
	std::vector<SDLEventFunction> SDLEventManager::m_event_functions_all = {};
	phmap::flat_hash_map<SDL_EventType,std::vector<SDLEventFunction>> SDLEventManager::m_event_functions = {};

	void SDLEventManager::add_event_function(SDLEventFunction event_function, bool all_events)
	{
		if(all_events)
			m_event_functions_all.emplace_back(event_function);
		else
			m_event_functions[event_function.event_type].emplace_back(event_function);
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