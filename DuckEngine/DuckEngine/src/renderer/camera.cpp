#include "Renderer/Camera.h"
#include "Renderer/Renderer.h"

namespace DE
{
Camera::Camera(fm::vec2 position, fm::vec2 size, f32 zoom)
	: Object("Camera"),
	m_position(position),
	m_size(size),
	m_zoom(zoom)
{
	m_sizeInverse = fm::vec2{1.f} / m_size;
	m_scale = fm::vec2{1.f, 1.f} * m_zoom;
}

void Camera::Update()
{
	SDL_Window* window = Renderer::GetWindow();
	int width_int, height_int;
	SDL_GetWindowSize(window, &width_int, &height_int);
	fm::vec2 window_size = {static_cast<f32>(width_int), static_cast<f32>(height_int)};

	m_scale = window_size / m_size * m_zoom;
}

void Camera::SetPosition(fm::vec2 position)
{
	m_position = position;
}

void Camera::SetSize(fm::vec2 size)
{
	m_size = size;
	m_sizeInverse = fm::vec2{1.f} / m_size;
}

void Camera::SetZoom(f64 zoom)
{
	m_zoom = zoom;
}
}
