#pragma once
#include "de/core.h"
#include "de/engine/object.h"

namespace de //DuckEngine
{
	class World;

	class DUCK_API GameInstance : public Object
	{
	public:
		//Make sure to call these parents!
		virtual void begin_play();
		virtual void update(f32 dt);
		virtual void end_play();

		World* get_world() { return m_world; }
	protected:
		World* m_world = nullptr;
	};
}