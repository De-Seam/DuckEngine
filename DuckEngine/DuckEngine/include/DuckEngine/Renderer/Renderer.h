#pragma once
#include "Core.h"
#include "Camera.h"

#include <SDL/SDL.h>

namespace DE
{
	class Renderer
	{
	public:
		static void Init();

		static void BeginFrame();
		static void EndFrame();

		static SDL_Window* GetWindow() { return m_window; }
		static SDL_Renderer* GetRenderer() { return m_renderer; }
		static Camera* GetCamera() { return m_camera; }
	private:
		static void Shutdown();

	private:
		static SDL_Window* m_window;
		static SDL_Renderer* m_renderer;
		static Camera* m_camera;

		friend class Engine; //Engine needs to do things like shutdown
	};
}