#pragma once
#include "de/core.h"

#include <SDL/SDL_events.h>
#include <phmap/phmap.h>

#include <vector>
#include <functional>

namespace de //DuckEngine
{
	struct SDLEventFunction
	{
		SDL_EventType event_type = SDL_EventType::SDL_FIRSTEVENT;
		std::function<void(SDL_Event&)> function_ptr = nullptr;
	};

	class DUCK_API SDLEventManager
	{
	public:
		static void add_event_function(SDLEventFunction event_function, bool all_events = false);
		static void update();

	private:
		static std::vector<SDLEventFunction> m_event_functions_all;
		static phmap::flat_hash_map<SDL_EventType,std::vector<SDLEventFunction>> m_event_functions;
	};
}