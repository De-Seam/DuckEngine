#pragma once
#include "de/core.h"
#include "quadtree.h"

namespace de //DuckEngine
{
	class DUCK_API CollisionManager
	{
	public:
		static void update(f32 dt);

	private:
		static Quadtree* m_quadtree;
	};
}