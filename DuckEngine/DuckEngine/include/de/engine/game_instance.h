#pragma once
#include "de/core.h"
#include "de/engine/object.h"

namespace de //DuckEngine
{
	class GameInstance
	{
	public:
		virtual void begin_play() {}
		virtual void update([[maybe_unused]] f32 dt) {}
		virtual void end_play() {}
	};
}