#pragma once
#include "Core.h"

#include <SDL/SDL.h>

#include <nlohmann/json.hpp>

namespace DE
{
	class DUCK_API Entity : public Object
	{
	public:
		Entity()
			: OBJECT{}

		virtual void BeginPlay();
		virtual void EndPlay();

		virtual void Update(f64 dt);
		virtual void Draw();

		std::string name;

		fm::vec2 position;
		double rotation;

		SDL_Texture* texture;

		std::string scriptPath;

		virtual void SetJSONVariables(nlohmann::json);
		virtual nlohmann::json GetJSONVariables() const;

	private:

	};
}