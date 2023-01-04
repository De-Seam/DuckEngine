#include "de/engine/game_instance.h"
#include "de/world/world.h"

namespace de
{
	void GameInstance::begin_play()
	{
		m_world->begin_play();
	}

	void GameInstance::update(f32 dt)
	{
		m_world->update(dt);
		m_world->draw();
	}

	void GameInstance::end_play()
	{
		m_world->end_play();
	}
}