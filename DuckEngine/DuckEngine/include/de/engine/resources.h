#pragma once
#include "de/renderer/renderer.h"
#include "resource_manager.h"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

namespace de//DuckEngine
{
	struct TextureResource : public Resource
	{
		virtual void load_resource(const std::string& file_name) override;

		SDL_Texture* texture = nullptr;
	};
}