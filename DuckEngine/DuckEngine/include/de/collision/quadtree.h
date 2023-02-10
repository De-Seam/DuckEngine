#pragma once
#include "de/core.h"
#include "de/utils/fmath.h"

#include "entt/entt.hpp"

#include <vector>

namespace de //DuckEngine
{
	class DUCK_API Quadtree : public Object
	{
		struct Node
		{
			fm::vec2 position, size;

			i32 left_first;
			i32 count; //>0 if a leave node
		};

	public:
		void add_entity(UID uid);

	private:
		Node m_root = {};
		std::vector<entt::entity> m_entities;
	};
}