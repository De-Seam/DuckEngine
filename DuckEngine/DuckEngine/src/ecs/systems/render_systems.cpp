#include "de/ecs/components/render_component.h"
#include "de/ecs/components/gameplay_component.h"
#include "de/ecs/systems/render_systems.h"
#include "de/engine/engine.h"
#include "de/renderer/renderer.h"

namespace de
{
	void render_systems(entt::registry& reg)
	{
		internal::rectangle_render_system(reg);
	}
}

namespace de::internal
{
	void internal::rectangle_render_system(entt::registry& reg)
	{
		auto view = reg.view<RenderRectangleComponent, RenderColorComponent, PositionComponent>();
		SDL_Renderer* renderer = Renderer::get_renderer();

		view.each([&](const entt::entity entity, 
			const RenderRectangleComponent& rectangle_c, 
			const RenderColorComponent& color_c, 
			const PositionComponent& position_c)
		{
				u32 rgba = color_c.color.get_rgba();
				u8 r = (rgba & 0xFF000000) >> 24;
				u8 g = (rgba & 0x00FF0000) >> 16;
				u8 b = (rgba & 0x0000FF00) >> 8;
				u8 a = (rgba & 0x000000FF);
				SDL_SetRenderDrawColor(renderer, r, g, b, a);
				SDL_FRect rect;
				rect.x = position_c.position.x;
				rect.y = position_c.position.y;
				rect.w = rectangle_c.size.x;
				rect.h = rectangle_c.size.x;
				SDL_RenderFillRectF(renderer, &rect);
		});
	}
}