#include "Renderer/Renderer.h"

namespace DE
{
	SDL_Window* Renderer::m_window = nullptr;
	SDL_Renderer* Renderer::m_renderer = nullptr;
	Camera* Renderer::m_camera = nullptr;

	void Renderer::Init()
	{
		Log(LogType::Message, "Initializing Renderer");

		SDL_SetMainReady();
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			Log("Error initializing SDL: %s\n", SDL_GetError());
			exit(1);
		}

		std::atexit(SDL_Quit);

		m_window = SDL_CreateWindow("DuckEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);

		u32 render_flags = SDL_RENDERER_ACCELERATED;
		m_renderer = SDL_CreateRenderer(m_window, -1, render_flags);

		m_camera = new Camera;
	}

	void Renderer::BeginFrame()
	{
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
		SDL_RenderClear(m_renderer);
	}

	void Renderer::EndFrame()
	{
		SDL_RenderPresent(m_renderer);
	}

	void Renderer::Shutdown()
	{
		Log(LogType::Message, "Renderer Shuting down");
	}
}