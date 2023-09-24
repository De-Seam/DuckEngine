#pragma once
#include "Core.h"

#include <SDL/SDL.h>

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

		virtual void Update(f64 dt);
		virtual void Draw();

		std::string name;

		fm::vec2 position;
		fm::vec2 size;
		double rotation;

		SDL_Texture* texture;

		std::string scriptPath;

		virtual void SetJSONVariables(nlohmann::json);
		virtual nlohmann::json GetJSONVariables() const;

	private:

	};
}