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

void Camera::Update(f64 dt)
{
	fm::vec2 windowSize = Renderer::GetWindowSize();

	m_scale = windowSize / m_size * m_zoom;

	m_zoom = fm::lerp(m_zoom, m_targetZoom, dt * m_zoomSpeed);
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
	m_targetZoom = fm::max(zoom, MIN_ZOOM);
}

void Camera::SnapZoom(f64 zoom)
{
	m_targetZoom = fm::max(zoom, MIN_ZOOM);
	m_zoom = m_targetZoom;
}

void Camera::SetZoomSpeed(f64 zoomSpeed)
{
	m_zoomSpeed = zoomSpeed;
}
}
