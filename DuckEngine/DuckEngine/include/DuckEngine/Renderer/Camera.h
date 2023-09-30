#pragma once
#include "Core.h"
#include "Object/Object.h"
#include "Utils/FMath.h"

namespace DE //DuckEngine
{
class Camera : public Object
{
public:
	Camera(fm::vec2 position = {0, 0}, fm::vec2 size = {1920.f, 1080.f}, f32 zoom = 1.f);

	virtual void Update();
	void SetPosition(fm::vec2 position);
	void SetSize(fm::vec2 size);
	void SetZoom(f64 zoom);

	fm::vec2 GetPosition() { return m_position; }
	fm::vec2 GetScale() { return m_scale; }
	f64 GetZoom() { return m_zoom; }

private:
	fm::vec2 m_position = {0.f, 0.f};
	fm::vec2 m_size = {1920.f, 1080.f};
	fm::vec2 m_sizeInverse = {1.f / 1920.f, 1.f / 1080.f};
	fm::vec2 m_scale = {1.f, 1.f};
	f64 m_zoom = 1.f;
};
}
