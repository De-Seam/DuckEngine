#include "de/ecs/functions/render_collisions.h"
#include "de/ecs/components/gameplay_components.h"
#include "de/ecs/components/render_components.h"
#include "de/engine/engine.h"
#include "de/renderer/renderer.h"
#include "de/renderer/camera.h"

namespace de
{
	entt::entity get_entity_id_at_point(fm::vec2 point, entt::registry& reg)
	{
		entt::entity rectangle_collision = get_entity_id_at_point_rectangles(point, reg);
		return rectangle_collision;
	}

	entt::entity get_entity_id_at_point_rectangles(fm::vec2 point, entt::registry& reg)
	{
		auto view = reg.view<RenderRectangleComponent, PositionComponent>();
		Camera* camera = Renderer::get_camera();
		if (!camera)
			return entt::null;
		fm::vec2 camera_position = camera->get_position();
		fm::vec2 camera_scale = camera->get_scale();

		entt::entity return_entity = entt::null;

		view.each([&](const entt::entity entity,
			const RenderRectangleComponent& rectangle_c,
			const PositionComponent& position_c)
			{
				fm::vec4 rectangle;
				rectangle.x = position_c.position.x - camera_position.x;
				rectangle.y = position_c.position.y - camera_position.y;
				rectangle.z = rectangle_c.size.x * camera_scale.x;
				rectangle.w = rectangle_c.size.y * camera_scale.y;

				if (point.x > rectangle.x && point.x < rectangle.x + rectangle.z
					&& point.y > rectangle.y && point.y < rectangle.y + rectangle.w)
					return_entity = entity;
			});

		return return_entity;
	}

}