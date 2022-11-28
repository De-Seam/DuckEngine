#pragma once
#include "de/core.h"

#include <entt/entt.hpp>
#include <phmap/phmap.h>

#include <unordered_map>

namespace de
{
	class Entity;

	class DUCK_API World
	{
	public:
		virtual void begin_play();
		virtual void end_play();

		virtual void update(f32 dt);
		virtual void draw();

		template<typename T>
		T* create_entity();
		void add_entity(Entity* entity);

		entt::registry& get_registry() { return m_registry; }

	protected:
		std::unordered_map<entt::entity, Entity*> m_entities;
		entt::registry m_registry; 

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