#include "de/entity/entity.h"
#include "de/world/world.h"

#include "de/ecs/components/gameplay_component.h"

namespace de
{
	Entity::~Entity()
	{
		entt::registry& reg = m_world->get_registry();

		reg.destroy(m_entity_id);
	}

	void Entity::destroy()
	{
		entt::registry& reg = m_world->get_registry();
		reg.emplace<DeathComponent>(m_entity_id);
	}
}