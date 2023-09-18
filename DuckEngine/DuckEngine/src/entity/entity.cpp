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
		name = json["name"];
		double positions[2] = { json["position"][0], json["position"][1] };
		position = { positions[0], positions[1] };
		rotation = json["rotation"];
		scriptPath = json["scriptPath"];
	}

	nlohmann::json Entity::GetJSONVariables() const
	{
		nlohmann::json json;
		json["name"] = name;
		json["position"] = { position.x, position.y };
		json["rotation"] = rotation;
		json["scriptPath"] = scriptPath;

		return json;
	}
}