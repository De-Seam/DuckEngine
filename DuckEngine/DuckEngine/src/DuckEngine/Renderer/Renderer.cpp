#include "Renderer/Renderer.h"

#include "DuckEngine/Entity/Entity.h"
#include "DuckEngine/World/World.h"
#include "DuckEngine/Engine/Engine.h"

namespace DE
{
SDL_Window* Renderer::m_window = nullptr;
SDL_Renderer* Renderer::m_renderer = nullptr;
Camera* Renderer::m_camera = nullptr;
fm::ivec2 Renderer::m_windowSize = {1280, 720};

void Renderer::Init()
{
	Log(LogType::Info, "Initializing Renderer");

	SDL_SetMainReady();
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		Log(LogType::Error, "Error initializing SDL: %s\n", SDL_GetError());
		exit(1);
	}

	if (std::atexit(SDL_Quit) != 0)
	{
		Log(LogType::Error, "Error assigning SDL_Quit to atexit.");
	}

	m_window = SDL_CreateWindow("DuckEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_windowSize.x,
								m_windowSize.y, SDL_WINDOW_RESIZABLE);

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

void Renderer::Update(f32 dt)
{
	m_camera->Update(dt);
}

void Renderer::DrawTexture(SDL_Texture* texture, const fm::vec2& position, const fm::vec2& size, double rotation)
{
	const SDL_FRect dstRect = GetSDLFRect(position, size);
	SDL_RenderCopyExF(m_renderer, texture, nullptr, &dstRect, rotation, nullptr, SDL_FLIP_NONE);
}

void Renderer::DrawTextureTinted(SDL_Texture* texture, const fm::vec2& position, const fm::vec2& size, double rotation,
								const fm::vec4& color)
{
	// Calculate color components
	const u32 argb = color.get_argb();
	const u8 a = (argb >> 24) & 0xFF;
	const u8 r = (argb >> 16) & 0xFF;
	const u8 g = (argb >> 8) & 0xFF;
	const u8 b = (argb >> 0) & 0xFF;

	// Set SDL render color
	SDL_SetTextureColorMod(texture, r, g, b);
	SDL_SetTextureAlphaMod(texture, a);

	const SDL_FRect dstRect = GetSDLFRect(position, size);
	SDL_RenderCopyExF(m_renderer, texture, nullptr, &dstRect, rotation, nullptr, SDL_FLIP_NONE);

	// Reset SDL render color
	SDL_SetTextureColorMod(texture, 255, 255, 255);
	SDL_SetTextureAlphaMod(texture, 255);
}

void Renderer::DrawRectangleOutline(const fm::vec2& position, const fm::vec2& size, const fm::vec4& color)
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

std::shared_ptr<Entity> Renderer::GetEntityAtPointSlow(fm::vec2 point)
{
	World* world = Engine::GetWorld();
	if (!world)
		return nullptr;

	const std::vector<std::shared_ptr<Entity>>& entities = world->GetEntities();
	for (const std::shared_ptr<Entity>& entity : entities)
	{
		fm::vec2 position = entity->GetPosition();
		fm::vec2 size = entity->GetHalfSize();
		f32 rotation = entity->GetRotation(); // Assuming rotation in radians
		rotation = fm::to_radians(rotation);

		fm::vec2 cameraPosition = m_camera->GetPosition();
		f32 cameraZoom = m_camera->GetZoom();

		// Calculate the screen position of the entity center
		fm::vec2 entityCenter = (position - cameraPosition) * cameraZoom;
		entityCenter.x += static_cast<f32>(m_windowSize.x) / 2.f; // Adjust for screen center
		entityCenter.y += static_cast<f32>(m_windowSize.y) / 2.f;

		// Calculate the half size of the object in screen space
		fm::vec2 halfSize = size * cameraZoom;

		// Apply the inverse rotation transformation to the point
		fm::vec2 rotatedPoint = point - entityCenter;
		f32 sinRotation = std::sinf(-rotation);
		f32 cosRotation = std::cosf(-rotation);
		fm::vec2 rotatedLocalPoint;
		rotatedLocalPoint.x = cosRotation * rotatedPoint.x - sinRotation * rotatedPoint.y;
		rotatedLocalPoint.y = sinRotation * rotatedPoint.x + cosRotation * rotatedPoint.y;

		// Check if the rotated local point is within the entity's bounds
		if (rotatedLocalPoint.x >= -halfSize.x && rotatedLocalPoint.x <= halfSize.x &&
			rotatedLocalPoint.y >= -halfSize.y && rotatedLocalPoint.y <= halfSize.y)
		{
			return entity; // Entity found at the given point
		}
	}

	return nullptr; // No entity found at the point
}

void Renderer::Shutdown()
{
	Log(LogType::Info, "Renderer Shutting down");

	delete m_camera;
}

SDL_Rect Renderer::GetSDLRect(const fm::vec2& position, const fm::vec2& halfSize)
{
	const fm::vec2 cameraPosition = m_camera->GetPosition();
	const f32 cameraZoom = m_camera->GetZoom();

	// Calculate the screen position of the center of the object
	const fm::vec2 screenCenter = (position - cameraPosition) * cameraZoom;

	// Calculate the half size of the object in screen space
	const fm::vec2 screenHalfSize = halfSize * cameraZoom;

	// Calculate the screen rectangle
	SDL_Rect sdlRect;
	sdlRect.x = static_cast<int>(screenCenter.x - halfSize.x) + (m_windowSize.x / 2);
	sdlRect.y = static_cast<int>(screenCenter.y - halfSize.y) + (m_windowSize.y / 2);
	sdlRect.w = static_cast<int>(screenHalfSize.x * 2);
	sdlRect.h = static_cast<int>(screenHalfSize.y * 2);

	return sdlRect;
}

SDL_FRect Renderer::GetSDLFRect(const fm::vec2& position, const fm::vec2& halfSize)
{
	const fm::vec2 cameraPosition = m_camera->GetPosition();
	const f32 cameraZoom = m_camera->GetZoom();

	// Calculate the screen position of the center of the object
	fm::vec2 screenCenter = (position - cameraPosition) * cameraZoom;

	// Calculate the screen half size
	fm::vec2 screenHalfSize = halfSize * cameraZoom;

	SDL_FRect sdlFRect;
	sdlFRect.x = screenCenter.x - screenHalfSize.x + static_cast<f32>(m_windowSize.x) * 0.5f;
	sdlFRect.y = screenCenter.y - screenHalfSize.y + static_cast<f32>(m_windowSize.y) * 0.5f;
	sdlFRect.w = screenHalfSize.x * 2;
	sdlFRect.h = screenHalfSize.y * 2;

	return sdlFRect;
}
}
