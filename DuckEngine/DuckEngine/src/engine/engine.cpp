#include "de/engine/engine.h"
#include "de/renderer/renderer.h"
#include "de/entity/entity.h"
#include "de/world/world.h"

#include "de/ecs/components/gameplay_component.h"
#include "de/ecs/components/render_component.h"

namespace de
{
	bool Engine::m_is_running = false;
	f32 Engine::m_delta_time = F32_EPSILON;

	World* Engine::m_world = nullptr;

	void Engine::init()
	{
		Renderer::init();

		m_world = new World;
		Entity* entity = m_world->create_entity<Entity>();
		PositionComponent& position_c = entity->add_component<PositionComponent>(fm::vec2(10.f, 10.f));
		entity->add_component<RenderRectangleComponent>(fm::vec2{80.f, 40.f});
		entity->add_component<RenderColorComponent>(fm::vec4(1.f, 1.f, 1.f, 1.f));

		m_is_running = true;
	}

	void Engine::shutdown()
	{
		m_is_running = false;
	}

	void Engine::begin_frame()
	{
		Renderer::begin_frame();
	}

	void Engine::update(f32 dt)
	{
		m_delta_time = dt;

		m_world->update(dt);
		m_world->draw();
	}

	void Engine::end_frame()
	{
		Renderer::end_frame();
	}

	void Engine::shutdown_internal()
	{
		Renderer::shutdown();

		exit(EXIT_SUCCESS);
	}
}