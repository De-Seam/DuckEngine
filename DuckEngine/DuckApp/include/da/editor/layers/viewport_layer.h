#pragma once
#include "layer.h"

#include "de/core.h"
#include "de/utils/fmath.h"

#include "entt/entt.hpp"

namespace da //DuckApp
{
	class ViewportLayer : public Layer
	{
	public:
		ViewportLayer();
		virtual void update(f32 dt) override;

	private:
		fm::vec2 m_mouse_position = {0.f,0.f};
		fm::vec2 m_position = {0.f,0.f};
		fm::vec2 m_size = {0.f, 0.f};
		entt::entity m_selected_entity = entt::null;
	};
}