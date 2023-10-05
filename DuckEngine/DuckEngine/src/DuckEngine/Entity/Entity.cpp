#include "Entity/Entity.h"

#include "Renderer/Renderer.h"
#include "Resources/ResourceManager.h"

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
	SetPosition({json["position"][0], json["position"][1]});
	SetSize({json["size"][0], json["size"][1]});
	SetRotation(json["rotation"]);
	SetScriptPath(json["scriptPath"]);

	if (json["texturePath"].is_string())
	{
		const std::string& textureFilePath = json["texturePath"];
		m_texture = ResourceManager::GetResource<TextureResource>(textureFilePath);
	}
}

nlohmann::json Entity::GetJSONVariables() const
{
	nlohmann::json json;
	json["name"] = m_name;
	json["position"] = {m_position.x, m_position.y};
	json["size"] = {m_size.x, m_size.y};
	json["rotation"] = m_rotation;
	json["scriptPath"] = m_scriptPath;
	if (m_texture)
		json["texturePath"] = m_texture->GetFilePath();

	return json;
}
}
