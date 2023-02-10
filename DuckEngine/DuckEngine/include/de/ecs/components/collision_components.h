#pragma once
#include "de/core.h"
#include "de/utils/fmath.h"

#include <entt/entt.hpp>

#include <functional>

namespace de //DuckEngine
{
	struct CollisionData
	{
		entt::entity entity;
	};

	enum class CollisionType
	{
		Static,
		Dynamic,
	};

	enum class CollisionChannel : u8
	{
		Static,
		Dynamic,
		Characters,
		Physics,
		Custom4,
		Custom5,
		Cusotm6,
		Custom7
	};

	//Also requires a CollisionShapeComponent
	struct CollisionComponent
	{
		CollisionComponent(CollisionType type) 
			: collision_type(type) {}

		CollisionType collision_type = CollisionType::Static; //Can not be modifier later
		std::function<void(CollisionData)> on_hit_function;
		CollisionChannel collision_channel = CollisionChannel::Static;
		u8 collision_checking = 0b10000000; //Static Only
		bool blocks_collision = true;

		void set_collision_blocking(CollisionChannel channel, bool blocking)
		{
			collision_checking ^= (-blocking ^ collision_checking) & (1UL << static_cast<u8>(channel));
		}

	};

	//Goes together with Transform Component
	struct CollisionRectangleComponent
	{
		fm::vec2 size;
	};
}