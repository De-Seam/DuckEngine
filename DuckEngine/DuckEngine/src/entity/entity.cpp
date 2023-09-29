#include "Entity/Entity.h"

#include "Renderer/Renderer.h"

namespace DE
{
void Entity::BeginPlay()
{ }

void Entity::EndPlay()
{ }

void Entity::Update(f64 dt)
{ }

void Entity::Draw()
{
	if (!m_texture)
	{
		Renderer::DrawRectangleOutline(m_position, m_size, {1, 1, 1, 1});
		return;
	}

	//SDL draw texture
	SDL_Texture* texture = m_texture->GetTexture();

	Renderer::DrawTexture(texture, m_position, m_size, m_rotation);
}

void Entity::SetJSONVariables(nlohmann::json json)
{
	SetName(json["name"]);
	double positions[2] = {json["position"][0], json["position"][1]};
	m_position = {positions[0], positions[1]};
	m_rotation = json["rotation"];
	m_scriptPath = json["scriptPath"];
}

nlohmann::json Entity::GetJSONVariables() const
{
	nlohmann::json json;
	json["name"] = m_name;
	json["position"] = {m_position.x, m_position.y};
	json["rotation"] = m_rotation;
	json["scriptPath"] = m_scriptPath;

	return json;
}
}
