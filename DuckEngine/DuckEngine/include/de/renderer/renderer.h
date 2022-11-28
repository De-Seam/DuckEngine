#pragma once
#include "de/core.h"

#include <SDL/SDL.h>

namespace de
{
	class DUCK_API Renderer
	{
	public:
		static void init();

		static void begin_frame();
		static void end_frame();

		static SDL_Window* get_window() { return m_window; }
		static SDL_Renderer* get_renderer() { return m_renderer; }
	private:
		static void shutdown();

	private:
		static SDL_Window* m_window;
		static SDL_Renderer* m_renderer;

		friend class Engine; //Engine needs to do things like shutdown
	};
}