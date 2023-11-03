#pragma once
#include "Core.h"

#include "Entity/Entity.h"

#include "nlohmann/json.hpp"

#include <box2d/box2d.h>

#include <vector>

namespace DE
{
class World
{
public:
	virtual void BeginPlay();
	virtual void EndPlay();

	virtual void Update(f32 dt);
	virtual void Draw();

	virtual void SaveToFile();
	virtual void SaveToFile(const std::string& filePath);
	virtual void LoadFromFile(const std::string& filePath);
	virtual nlohmann::json SaveToJson();
	virtual void LoadFromJson(const nlohmann::json& json);

	template<typename T>
	T* CreateEntity();

	const std::string& GetName() { return m_name; }
	const std::string& GetFilePath() { return m_filePath; }

	b2World* GetPhysicsWorld() const { return m_physicsWorld.get(); }

public:
	const std::vector<std::shared_ptr<Entity>>& GetEntities() { return m_entities; }

private:
	std::vector<std::shared_ptr<Entity>> m_entities;

	std::string m_name = "World";
	std::string m_filePath = "Assets/Worlds/World.DuckWorld";

	std::unique_ptr<b2World> m_physicsWorld = std::make_unique<b2World>(b2Vec2{0.f, -9.8f});
};

template<typename T>
T* World::CreateEntity()
{
	std::shared_ptr<T>& entity = m_entities.emplace_back(std::move(std::make_unique<T>()));
	return entity.get();
}
}
