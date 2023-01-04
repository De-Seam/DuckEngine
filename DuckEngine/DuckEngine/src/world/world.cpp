#include "de/world/world.h"

#include "de/ecs/components/gameplay_components.h"
#include "de/ecs/systems/render_systems.h"

#include "de/entity/entity.h"

#include <stdio.h>
#include <stdlib.h>

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
		for(const auto& entity_pair : m_entities)
			entity_pair.second->draw();

		render_systems(m_registry);
	}

	void World::load_from_data(const char* data)
	{
		m_save_document.Parse(data);
		rapidjson::Value& entities = m_save_document["entities"];
		rapidjson::GenericArray entities_array = entities.GetArray();

		for(auto& entity_value : entities_array)
		{
			Entity* entity = this->create_entity<Entity>();
			entity->load_from_value(entity_value);
		}
	}

	void World::load_from_file(const std::string& file_name)
	{
		//Open file
		FILE* file;
		if(fopen_s(&file, file_name.c_str(), "rb") != 0 || file == nullptr)
		{
			log(LogType::error, "Error opening file");
			return;
		}
		//Determine file size
		fseek(file, 0, SEEK_END);
		i32 file_size = ftell(file);
		rewind(file);
		//Create buffer
		char* buffer = static_cast<char*>(malloc(sizeof(char) * file_size));
		if(buffer == nullptr)
		{
			log(LogType::error, "Error creating buffer");
			return;
		}
		//Read file to buffer
		u_size result = static_cast<u_size>(fread(buffer, 1, file_size, file));
		if(result != file_size)
		{
			log(LogType::error, "Error reading file to buffer");
			return;
		}
		//Load data from buffer
		load_from_data(buffer);
		//Cleanup
		fclose(file);
		free(buffer);
	}

	const char* World::save_to_data()
	{
		return nullptr;
	}

	void World::save_to_file(const std::string& file_name)
	{
		(void)file_name;
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