#pragma once
#include "de/engine/game_instance.h"
#include "de/world/world.h"
#include "de/entity/entity.h"

#include "de/ecs/components/gameplay_components.h"
#include "de/ecs/components/render_components.h"

class TestGameInstance : public de::GameInstance
{
public:
	virtual void begin_play() override
	{
		m_world = new de::World;

		de::GameInstance::begin_play();

		de::Entity* entity = m_world->create_entity<de::Entity>();
		de::PositionComponent& position_c = entity->add_component<de::PositionComponent>(fm::vec2(10.f, 10.f));
		entity->add_component<de::RenderRectangleComponent>(fm::vec2{80.f, 40.f});
		entity->add_component<de::RenderColorComponent>(fm::vec4(1.f, 1.f, 1.f, 1.f));
	}

	virtual void update(f32 dt) override
	{
		de::GameInstance::update(dt);
	}

	virtual void end_play() override
	{
		de::GameInstance::end_play();
	}

private:

};