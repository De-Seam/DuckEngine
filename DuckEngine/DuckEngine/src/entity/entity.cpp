#include "de/entity/entity.h"
#include "de/world/world.h"

#include "de/ecs/components/gameplay_components.h"

namespace de
{
	Entity::~Entity()
	{
		entt::registry& reg = m_world->get_registry();

		reg.destroy(m_entity_id);
	}

	void Entity::load_from_value(rapidjson::Value& value)
	{
		 m_name = value["name"].GetString();
	}

	void Entity::save_to_value()
	{
	}

	void Entity::destroy()
	{
		entt::registry& reg = m_world->get_registry();
		reg.emplace<DeathComponent>(m_entity_id);
	}
}