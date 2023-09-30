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

	m_camera = new Camera();
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

void Renderer::DrawTexture(SDL_Texture* texture, fm::vec2 position, fm::vec2 size, double rotation)
{
	const SDL_Rect dstRect = GetSDLRect(position, size);
	SDL_RenderCopyEx(m_renderer, texture, nullptr, &dstRect, rotation, nullptr, SDL_FLIP_NONE);
}

void Renderer::DrawRectangleOutline(fm::vec2 position, fm::vec2 size, fm::vec4 color)
{
	// Calculate color components
	const u32 argb = color.get_argb();
	const u8 a = (argb >> 24) & 0xFF;
	const u8 r = (argb >> 16) & 0xFF;
	const u8 g = (argb >> 8) & 0xFF;
	const u8 b = (argb >> 0) & 0xFF;

	// Set SDL render color
	SDL_SetRenderDrawColor(m_renderer, r, g, b, a);

	const SDL_Rect rect = GetSDLRect(position, size);
	// Draw rectangle outline
	SDL_RenderDrawRect(m_renderer, &rect);
}


void Renderer::Shutdown()
{
	Log(LogType::Message, "Renderer Shutting down");

	delete m_camera;
}

SDL_Rect Renderer::GetSDLRect(const fm::vec2& position, const fm::vec2& size)
{
	const fm::vec2 cameraPosition = m_camera->GetPosition();
	const double cameraZoom = m_camera->GetZoom();

	// Translate the position based on the camera's position
	fm::vec2 translatedPosition;
	translatedPosition.x = (position.x - cameraPosition.x) * cameraZoom;
	translatedPosition.y = (position.y - cameraPosition.y) * cameraZoom;

	// Scale the size based on the camera's zoom
	fm::vec2 scaledSize;
	scaledSize.x = size.x * cameraZoom;
	scaledSize.y = size.y * cameraZoom;

	// Create SDL_Rect based on translated and scaled values
	SDL_Rect rect;
	rect.x = static_cast<i32>(translatedPosition.x - scaledSize.x); // Top-left x
	rect.y = static_cast<i32>(translatedPosition.y - scaledSize.y); // Top-left y
	rect.w = static_cast<i32>(scaledSize.x * 2); // Full width
	rect.h = static_cast<i32>(scaledSize.y * 2); // Full height

	return rect;
}
}
