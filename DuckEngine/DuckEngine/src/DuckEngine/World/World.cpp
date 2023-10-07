#include "World/World.h"
#include "DuckEngine/Entity/Entity.h"

#include <fstream>
#include <ostream>

namespace DE
{
void World::BeginPlay()
{
	for (u_size i = 0; i < m_entities.size(); i++)
	{
		m_entities[i]->BeginPlay();
	}
}

void World::EndPlay()
{
	for (u_size i = 0; i < m_entities.size(); i++)
	{
		m_entities[i]->EndPlay();
	}
}

void World::Update(f64 dt)
{
	for (u_size i = 0; i < m_entities.size(); i++)
	{
		m_entities[i]->Update(dt);
	}
}

void World::Draw()
{
	for (u_size i = 0; i < m_entities.size(); i++)
	{
		m_entities[i]->Draw();
	}
}

void World::SaveToFile()
{
	SaveToFile(m_filePath);
}

void World::SaveToFile(const std::string& filePath)
{
	std::ofstream file(filePath);
	file << std::setw(3) << SaveToJson();
}

void World::LoadFromFile(const std::string& filePath)
{
	std::ifstream file(filePath);
	nlohmann::json json;
	file >> json;

	LoadFromJson(json);
}

nlohmann::json World::SaveToJson()
{
	nlohmann::json json;
	json["Name"] = m_name;
	for (u_size i = 0; i < m_entities.size(); i++)
	{
		json["Entities"] += m_entities[i]->GetJSONVariables();
	}
	return json;
}

void World::LoadFromJson(const nlohmann::json& json)
{
	m_name = json["Name"];
	for (u_size i = 0; i < json["Entities"].size(); i++)
	{
		Entity* entity = CreateEntity<Entity>();
		entity->SetJSONVariables(json["Entities"][i]);
	}
}
}
