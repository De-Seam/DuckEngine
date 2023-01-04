#pragma once
#include "de/core.h"
#include "de/engine/object.h"
#include "de/world/world.h"

#include <entt/entt.hpp>
#include <rapidjson/document.h>

#include <cassert>

namespace de
{
	class World;

	class DUCK_API Entity : public Object
	{
	public:
		~Entity();

		virtual void begin_play() {}; //Begin play called after beginning play
		virtual void end_play() {}; //End play called before ending play
		
		virtual void update([[maybe_unused]] f32 dt) {}; //Update called every tick
		virtual void draw() {}; //Additional draw calls.

		//Make sure to call these parent functions as well.
		virtual void load_from_value(rapidjson::Value& value);
		virtual void save_to_value();

		void destroy();

		template<typename T, typename... Args>
		T& add_component(Args&&... args);
		template<typename T, typename... Args>
		T& add_or_replace_component(Args&&... args);
		template<typename T>
		T& get_component();
		template<typename T>
		bool has_component();
		template<typename T>
		void remove_component();

	protected:
		std::string m_name = "Entity";

	private:
		entt::entity m_entity_id = entt::null;
		World* m_world = nullptr;

		friend class World;
	};



	template<typename T, typename... Args>
	inline T& Entity::add_component(Args&&... args)
	{
		assert(!has_component<T>() && "Entity already has component!");
		T& component = m_world->get_registry().emplace<T>(m_entity_id, std::forward<Args>(args)...);
		return component;
	}

	template<typename T, typename... Args>
	inline T& Entity::add_or_replace_component(Args&&... args)
	{
		T& component = m_world->get_registry().emplace_or_replace<T>(m_entity_id, std::forward<Args>(args)...);
		return component;
	}

	template<typename T>
	inline T& Entity::get_component()
	{
		assert(has_component<T>() && "Entity does not have component!");
		return m_world->get_registry().get<T>(m_entity_id);
	}

	template<typename T>
	inline bool Entity::has_component()
	{
		return m_world->get_registry().any_of<T>(m_entity_id);
	}

	template<typename T>
	inline void Entity::remove_component()
	{
		assert(has_component<T>() && "Entity does not have component!");
		 m_world->get_registry().remove<T>(m_entity_id);
	}
}