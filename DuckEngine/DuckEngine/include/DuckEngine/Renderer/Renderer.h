#pragma once
#include "Core.h"
#include "Camera.h"

#include <SDL/SDL.h>

namespace DE
{
class Entity;

class Renderer
{
public:
	static void Init();

	static void BeginFrame();
	static void EndFrame();

	static void Update(f32 dt);

	static void DrawTexture(SDL_Texture* texture, const fm::vec2& position, const fm::vec2& size, double rotation);
	static void DrawTextureTinted(SDL_Texture* texture, const fm::vec2& position, const fm::vec2& size, double rotation,
								const fm::vec4& color);
	static void DrawRectangleOutline(const fm::vec2& position, const fm::vec2& size, const fm::vec4& color);

	static SDL_Window* GetWindow() { return m_window; }
	static SDL_Renderer* GetRenderer() { return m_renderer; }
	static Camera* GetCamera() { return m_camera; }
	static fm::ivec2 GetWindowSize() { return m_windowSize; }

	[[nodiscard]] static std::shared_ptr<Entity> GetEntityAtPointSlow(fm::vec2 point);

private:
	static void Shutdown();

	static SDL_Rect GetSDLRect(const fm::vec2& position, const fm::vec2& size);
	static SDL_FRect GetSDLFRect(const fm::vec2& position, const fm::vec2& halfSize);

private:
	static SDL_Window* m_window;
	static SDL_Renderer* m_renderer;
	static Camera* m_camera;

	static fm::ivec2 m_windowSize;

	friend class Engine; //Engine needs to do things like shutdown
	friend class Editor; //For editing window size
};
}
