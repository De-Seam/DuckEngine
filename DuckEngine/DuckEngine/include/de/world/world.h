#pragma once
#include "de/core.h"
#include "de/engine/object.h"

#include <entt/entt.hpp>
#include <phmap/phmap.h>

namespace de
{
	class Entity;

	class DUCK_API World : public Object
	{
	public:
		virtual void begin_play();
		virtual void end_play();

		virtual void update(f32 dt);
		virtual void draw();

		template<typename T>
		T* create_entity();
		void add_entity(Entity* entity);
		Entity* get_entity(entt::entity entity_id) { return m_entities[entity_id];}

		entt::registry& get_registry() { return m_registry; }

	protected:
		phmap::flat_hash_map<entt::entity, Entity*> m_entities = {};
		entt::registry m_registry = {}; 

	private:
		void delete_entities();

	};

	template<typename T>
	inline T* World::create_entity()
	{
		T* entity = new T;
		add_entity(entity);
		return entity;
	}
}