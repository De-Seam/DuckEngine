#pragma once
#include "Core.h"
#include "Resources/ResourceTypes/TextureResource.h"

#include <nlohmann/json.hpp>

namespace DE
{
class Entity : public Object
{
public:
	Entity()
		: Object("Entity") {}

	virtual void BeginPlay();
	virtual void EndPlay();

	virtual void Update(f32 dt);
	virtual void Draw();

	const std::string& GetName() const { return m_name; }
	fm::vec2 GetPosition() const { return m_position; }
	fm::vec2 GetSize() const { return m_size; }
	f32 GetRotation() const { return m_rotation; }
	std::shared_ptr<TextureResource> GetTexture() const { return m_texture; }
	const std::string& GetScriptPath() const { return m_scriptPath; }

	void SetName(const std::string& name) { m_name = name; }
	void SetPosition(const fm::vec2& position) { m_position = position; }
	void SetSize(const fm::vec2& size) { m_size = size; }
	void SetRotation(f32 rotation) { m_rotation = fmodf(rotation + 180.f, 360.f) - 180.f; }
	void SetTexture(const std::shared_ptr<TextureResource>& texture) { m_texture = texture; }
	void SetScriptPath(const std::string& scriptPath) { m_scriptPath = scriptPath; }

	virtual void SetJSONVariables(nlohmann::json);
	virtual nlohmann::json GetJSONVariables() const;

private:
	std::string m_name;

	fm::vec2 m_position;
	fm::vec2 m_size;
	f32 m_rotation;

	std::shared_ptr<TextureResource> m_texture;
	std::string m_scriptPath;

	friend class InspectorLayer;
};
}
