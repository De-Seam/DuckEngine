#pragma once
#include "de/core.h"
#include "de/engine/object.h"
#include "de/utils/fmath.h"

namespace de //DuckEngine
{
	class DUCK_API Camera : public Object
	{
	public:
		Camera(fm::vec2 position = {0.f, 0.f}, fm::vec2 size = {1920.f, 1080.f}, f32 zoom = 1.f);

		virtual void update();
		void set_position(fm::vec2 position);
		void set_size(fm::vec2 size);
		void set_zoom(f32 zoom);

		fm::vec2 get_position() { return m_position; }
		fm::vec2 get_scale() { return m_scale; }
	private:
		fm::vec2 m_position = {0.f,0.f};
		fm::vec2 m_size = {1920.f, 1080.f};
		fm::vec2 m_size_inverse = {1.f/1920.f, 1.f/1080.f};
		fm::vec2 m_scale = {1.f, 1.f};
		f32 m_zoom = 1.f;
	};
}