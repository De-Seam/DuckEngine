#pragma once
#include "de/core.h"
#include "de/utils/fmath.h"
#include "de/engine/engine.h"
#include "de/world/world.h"

#include <entt/entt.hpp>

namespace de
{
	entt::entity get_entity_id_at_point(fm::vec2 point, entt::registry& reg = Engine::get_world()->get_registry());
	entt::entity get_entity_id_at_point_rectangles(fm::vec2 point, entt::registry& reg = Engine::get_world()->get_registry());
}
