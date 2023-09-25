#pragma once
#include "Core.h"
#include "Object/Object.h"

#include <SDL/SDL_events.h>
#include <phmap/phmap.h>

#include <vector>
#include <functional>

namespace DE //DuckEngine
{
	struct SDLEventFunction : public Object
	{
		SDLEventFunction() : OBJECT{}
			SDLEventFunction(SDL_EventType event_type, std::function<void(SDL_Event&)> function_ptr)
			: OBJECT, event_type(event_type), function_ptr(function_ptr) {}

		SDL_EventType event_type = SDL_EventType::SDL_FIRSTEVENT;
		std::function<void(SDL_Event&)> function_ptr = nullptr;
	};

	class SDLEventManager
	{
	public:
		static void RemoveEventFunction(UID uid);
		static UID AddEventFunction(SDLEventFunction event_function, bool all_events = false);
		static void Update();

	private:
		static std::vector<SDLEventFunction> m_eventsFunctionAll;
	};
}