#include "Events/SDLEventManager.h"
#include "Engine/Engine.h"
#include "Utils/fmath.h"

namespace DE
{
	std::vector<SDLEventFunction> SDLEventManager::m_eventsFunctionAll = {};
	phmap::flat_hash_map<SDL_EventType, std::vector<SDLEventFunction>> g_eventFunctions = {};

	void SDLEventManager::RemoveEventFunction(UID uid)
	{
		SDLEventFunction* event_function = static_cast<SDLEventFunction*>(Engine::GetObject(uid));
		for (size_t i = 0; i < m_eventsFunctionAll.size(); i++)
		{
			if (m_eventsFunctionAll[i].GetUID() == event_function->GetUID())
			{
				fm::swap(m_eventsFunctionAll[i], m_eventsFunctionAll.back());
				m_eventsFunctionAll.pop_back();
			}
		}
		std::vector<SDLEventFunction>& event_functions = g_eventFunctions[event_function->event_type];
		for (size_t i = 0; i < event_functions.size(); i++)
		{
			if (event_functions[i].GetUID() == event_function->GetUID())
			{
				fm::swap(event_functions[i], event_functions.back());
				event_functions.pop_back();
			}
		}
	}

	UID SDLEventManager::AddEventFunction(SDLEventFunction event_function, bool all_events)
	{
		if (all_events)
			m_eventsFunctionAll.emplace_back(event_function);
		else
		{
			g_eventFunctions[event_function.event_type].emplace_back(event_function);
		}

		return event_function.GetUID();
	}

	void SDLEventManager::Update()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			for (SDLEventFunction& event_function : m_eventsFunctionAll)
				event_function.function_ptr(event);

			std::vector<SDLEventFunction>& event_array = g_eventFunctions[static_cast<SDL_EventType>(event.type)];
			for (SDLEventFunction& event_function : event_array)
				event_function.function_ptr(event);
		}
	}
}