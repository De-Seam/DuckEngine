#include "de/engine/resources.h"

namespace de //DuckEngine
{
	void TextureResource::load_resource(const std::string& file_name)
	{
		texture = IMG_LoadTexture(de::Renderer::get_renderer(), file_name.c_str());
	}
}