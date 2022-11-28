#pragma once
#include "de/core.h"
#include "de/utils/fmath.h"

namespace de
{
	struct PositionComponent
	{
		fm::vec2 position;
	};

	//Assign this to delete an entity
	struct DeathComponent 
	{};
}