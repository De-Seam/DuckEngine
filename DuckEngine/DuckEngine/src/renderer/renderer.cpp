#include "de/renderer/renderer.h"

namespace de
{
	SDL_Window* Renderer::m_window = nullptr;
	SDL_Renderer* Renderer::m_renderer = nullptr;

	void Renderer::init()
	{
		SDL_SetMainReady();
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
			log("error initializing SDL: %s\n", SDL_GetError());

		m_window = SDL_CreateWindow("ProjectM", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);

		u32 render_flags = SDL_RENDERER_ACCELERATED;
		m_renderer = SDL_CreateRenderer(m_window, -1, render_flags);
	}

	void Renderer::begin_frame()
	{
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
		SDL_RenderClear(m_renderer);
	}

	void Renderer::end_frame()
	{
		SDL_RenderPresent(m_renderer);
	}

	void Renderer::shutdown()
	{
		SDL_Quit();
	}
}