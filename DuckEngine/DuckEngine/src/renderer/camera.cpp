#include "de/renderer/camera.h"
#include "de/renderer/renderer.h"

namespace de
{
	Camera::Camera(fm::vec2 position,  fm::vec2 size, f32 zoom)
		: m_position(position),
		m_size(size),
		m_zoom(zoom)
	{
		m_size_inverse = fm::vec2{1.f} / m_size;
		m_scale = fm::vec2{1.f, 1.f} * m_zoom;
	}

	void Camera::update()
	{
		SDL_Window* window = de::Renderer::get_window();
		int width_int, height_int;
		SDL_GetWindowSize(window, &width_int, &height_int);
		fm::vec2 window_size = {static_cast<f32>(width_int), static_cast<f32>(height_int)};

		m_scale = window_size / m_size * m_zoom;
	}

	void Camera::set_position(fm::vec2 position)
	{
		m_position = position;
	}

	void Camera::set_size(fm::vec2 size)
	{
		m_size = size;
		m_size_inverse = fm::vec2{1.f} / m_size;
	}

	void Camera::set_zoom(f32 zoom)
	{
		m_zoom = zoom;
	}
}