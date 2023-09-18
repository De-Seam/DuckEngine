#pragma once
#include "Core.h"

#include "Entity/Entity.h"

#include "nlohmann/json.hpp"

namespace DE
{
	class DUCK_API World
	{
	public:

		virtual void BeginPlay();
		virtual void EndPlay();

		virtual void Update(f64 dt);
		virtual void Draw();

		virtual void LoadFromFile(const std::string& filePath);
		virtual void SaveToFile(const std::string& filePath);
	private:

		Array<Entity*> m_entities;

		std::string m_name = "World";
	};
}