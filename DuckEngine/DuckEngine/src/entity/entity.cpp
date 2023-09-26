#include "Entity/Entity.h"

namespace DE
{
	void Entity::BeginPlay()
	{
	}

	void Entity::EndPlay()
	{
	}

	void Entity::Update(f64 dt)
	{
	}

	void Entity::Draw()
	{
	}

	void Entity::SetJSONVariables(nlohmann::json json)
	{
		SetName(json["name"]);
		double positions[2] = { json["position"][0], json["position"][1] };
		m_position = { positions[0], positions[1] };
		m_rotation = json["rotation"];
		m_scriptPath = json["scriptPath"];
	}

	nlohmann::json Entity::GetJSONVariables() const
	{
		nlohmann::json json;
		json["name"] = m_name;
		json["position"] = { m_position.x, m_position.y };
		json["rotation"] = m_rotation;
		json["scriptPath"] = m_scriptPath;

		return json;
	}
}