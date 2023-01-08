#pragma once
#include "de/core.h"
#include "de/utils/fmath.h"

namespace de
{
	struct TextureResource;

	struct DUCK_API RenderTextureComponent
	{
		RenderTextureComponent(TextureResource* resource);
		RenderTextureComponent(const std::string& file_name);
		TextureResource* texture_resource;
	};

	struct RenderColorComponent
	{
		fm::vec4 color;
	};

	//Render a rectangle. Requires position component and either color or texture component
	struct RenderRectangleComponent
	{
		fm::vec2 size;
	};
}