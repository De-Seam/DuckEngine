#include "World/World.h"

#include <fstream>

namespace DE
{
	void World::BeginPlay()
	{
		for (u_size i = 0; i < m_entities.Size(); i++)
		{
			m_entities[i]->BeginPlay();
		}
	}

	void World::EndPlay()
	{
		for (u_size i = 0; i < m_entities.Size(); i++)
		{
			m_entities[i]->EndPlay();
		}
	}

	void World::Update(f64 dt)
	{
		for (u_size i = 0; i < m_entities.Size(); i++)
		{
			m_entities[i]->Update(dt);
		}
	}

	void World::Draw()
	{
		for (u_size i = 0; i < m_entities.Size(); i++)
		{
			m_entities[i]->Draw();
		}
	}

	void World::LoadFromFile(const std::string& filePath)
	{
		std::ifstream file(filePath);
		nlohmann::json json;
		file >> json;

		m_name = json["Worlds"]["Name"];
		for (u_size i = 0; i < json["Worlds"][m_name]["Entities"].size(); i++)
		{
			Entity* entity = new Entity;
			entity->SetJSONVariables(json["Worlds"][m_name]["Entities"][std::to_string(i)]);
			m_entities.Add(entity);
		}
	}

	void World::SaveToFile(const std::string& filePath)
	{
		nlohmann::json json;
		json["Worlds"]["Name"] = m_name;
		for (u_size i = 0; i < m_entities.Size(); i++)
		{
			json["Worlds"][m_name]["Entities"][std::to_string(i)] = m_entities[i]->GetJSONVariables();
		}

		std::ofstream file(filePath);
		file << json;
	}
}