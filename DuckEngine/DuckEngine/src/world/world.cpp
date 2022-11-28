#include "de/world/world.h"

#include "de/ecs/components/gameplay_component.h"
#include "de/ecs/systems/render_systems.h"

#include "de/entity/entity.h"

namespace de
{
	void World::begin_play()
	{
	}

	void World::end_play()
	{
	}

	void World::update(f32 dt)
	{
		for(auto entity_pair : m_entities)
			entity_pair.second->update(dt);

		delete_entities();
	}

	void World::draw()
	{
		for(auto entity_pair : m_entities)
			entity_pair.second->draw();

		render_systems(m_registry);
	}

	void World::add_entity(Entity* entity)
	{
		entity->m_entity_id = m_registry.create();
		entity->m_world = this;
		m_entities[entity->m_entity_id] = entity;
	}

	void World::delete_entities()
	{
		auto view = m_registry.view<DeathComponent>();

		view.each([&](const entt::entity entity)
		{
			delete m_entities[entity];
			m_entities.erase(entity);
		});
	}
}