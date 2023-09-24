#pragma once
#include "Core.h"

#include "Entity/Entity.h"

#include "nlohmann/json.hpp"

#include <vector>

namespace DE
{
	class World
	{
	public:

		virtual void BeginPlay();
		virtual void EndPlay();

		virtual void Update(f64 dt);
		virtual void Draw();

		virtual void SaveToFile();
		virtual void SaveToFile(const std::string& filePath);
		virtual void LoadFromFile(const std::string& filePath);
		virtual nlohmann::json SaveToJson();
		virtual void LoadFromJson(const nlohmann::json& json);

		template<typename T>
		T* CreateEntity();
	private:

		std::vector<std::unique_ptr<Entity>> m_entities;

		std::string m_name = "World";
		std::string m_filePath = "Assets/Worlds/World.json";
	};

	template<typename T>
	inline T* World::CreateEntity()
	{
		std::unique_ptr<T>&  entity = m_entities.emplace_back(std::move(std::make_unique<T>()));
		return entity.get();
	}
}