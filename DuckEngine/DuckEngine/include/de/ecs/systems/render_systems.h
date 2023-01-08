#pragma once
#include "de/core.h"

#include <entt/entt.hpp>

namespace de
{
	void render_systems(entt::registry& reg);

	namespace internal
	{
		void rectangle_render_system(entt::registry& reg);
		void texture_render_system(entt::registry& reg);
	}
}