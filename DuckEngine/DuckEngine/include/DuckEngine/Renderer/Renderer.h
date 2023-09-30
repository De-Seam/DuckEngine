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

	static void DrawTexture(SDL_Texture* texture, fm::vec2 position, fm::vec2 size, double rotation);
	static void DrawRectangleOutline(fm::vec2 position, fm::vec2 size, fm::vec4 color);

	static SDL_Window* GetWindow() { return m_window; }
	static SDL_Renderer* GetRenderer() { return m_renderer; }
	static Camera* GetCamera() { return m_camera; }

private:
	static void Shutdown();

	static SDL_Rect GetSDLRect(const fm::vec2& position, const fm::vec2& size);

private:
	static SDL_Window* m_window;
	static SDL_Renderer* m_renderer;
	static Camera* m_camera;

	friend class Engine; //Engine needs to do things like shutdown
};
}
