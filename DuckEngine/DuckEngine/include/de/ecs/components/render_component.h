#pragma once
#include "de/core.h"
#include "de/utils/fmath.h"

namespace de
{
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